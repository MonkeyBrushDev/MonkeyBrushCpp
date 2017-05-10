#include "Node.hpp"

namespace mb
{
  Node::Node( )
    : Node( std::string( "Node" ) )
  {
  }
  Node::Node( const std::string& name )
  : _parent( nullptr )
  , _name( name )
  , tag( std::string("Nothing") )
  {
  }

  Node::~Node( )
  {
    std::cout << "[D] Node '" << this->name( ) << "'" << std::endl;
    detachAllComponents( );
  }

  std::string Node::name( ) const
  {
    return _name;
  }

  void Node::name( const std::string& name )
  {
    _name = name;
  }

  void Node::perform( Visitor &visitor )
  {
    visitor.traverse( this );
  }

  void Node::perform( const Visitor &visitor )
  {
    const_cast< Visitor& >( visitor ).traverse( this );
  }

  void Node::accept( Visitor &visitor )
  {
    visitor.visitNode( this );
  }

  bool Node::hasParent( void ) const
  {
    return _parent != nullptr;
  }

  Node* Node::parent( void )
  {
    return _parent;
  }

  void Node::parent( Node* p )
  {
    _parent = p;
  }

  void Node::startComponents( )
  {
    forEachComponent( [] ( Component* c ) {
      c->start( );
    } );
  }

  void Node::addComponent( Component* comp )
  {
    comp->setNode( this );
    _components.insert( std::pair<std::string, Component*>( comp->GetUID( ), comp ) );
    comp->onAttach( );
  }

  void Node::updateComponents( const float& dt )
  {
    for ( auto& comp : _components )
    {
      if ( comp.second->activo )
      {
        comp.second->update( dt );
      }
    }
  }
  void Node::detachAllComponents( void )
  {
    forEachComponent( [] ( Component *cmp )
    {
      cmp->onDetach( );
      cmp->setNode( nullptr );
    } );

    _components.clear( );
  }

  void Node::forEachComponent( std::function< void( Component * ) > callback )
  {
    // create a copy of the component's collection
    // to prevent errors when attaching or detaching
    // components during an update pass
    auto cs = _components;
    for ( auto cmp : cs )
    {
      if ( cmp.second != nullptr )
      {
        callback( cmp.second );
      }
    }
  }

  Component* Node::getComponentByName( const std::string& name )
  {
    auto aux = _components.find( name );
    if ( aux == _components.end( ) )
    {
      return nullptr;
    }
    return aux->second;
  }

  Component* getComponentByName( const std::string& name );
  std::vector<Component*>Node::getComponentsByName( const std::string& name )
  {
    std::vector<Component*> cs;

    auto finds = _components.equal_range( name );

    std::transform( finds.first, finds.second,
      std::back_inserter( cs ), [] ( std::pair<std::string, Component*> element ){
      return element.second;
    } );

    return cs;
  }
}
