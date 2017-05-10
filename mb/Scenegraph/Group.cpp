#include "Group.hpp"

namespace mb
{
  Group::Group( const std::string name )
  : Node( name )
  {
  }

  Group::~Group( )
  {
    std::cout << "[D] Group '" << this->name( ) << "'" << std::endl;
    removeChildren( );
  }

  bool Group::hasNodes( void ) const
  {
    return !_children.empty( );
  }
  unsigned int Group::numChildren( void ) const
  {
    return _children.size( );
  }

  void Group::addChild( Node* node )
  {
    if ( node->parent( ) == this )
    {
      return;
    }
    if ( node->parent( ) != nullptr )
    {
      throw "HasParentException";
    }
    node->parent( this );
    _children.push_back( node );
  }

  void Group::removeChild( Node* n )
  {
    if ( n->parent( ) == this )
    {
      _children.erase( std::remove( _children.begin( ), _children.end( ), n ), _children.end( ) );
      n->parent( nullptr );
    }
  }
  #include <algorithm>
  void Group::removeChildren( void )
  {
    std::for_each( _children.begin( ), _children.end( ), [] ( Node* n )
    {
      n->parent( nullptr );
      delete n;
    } );
    _children.clear( );
  }

  Node* Group::nodeAt( unsigned int idx )
  {
    return _children.at( idx );
  }

  void Group::forEachNode( std::function< void( Node * ) > callback )
  {
    std::for_each( _children.begin( ), _children.end( ), [&] ( Node* n )
    {
      /* TODO if ( n->isEnabled( ) )
      {*/
      callback( n );
      /*}*/
    } );
  }
  void Group::accept( Visitor& v )
  {
    v.visitGroup( this );
  }
}
