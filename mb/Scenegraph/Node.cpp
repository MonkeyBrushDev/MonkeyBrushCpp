/**
 * Copyright (c) 2017, Monkey Brush
 * All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

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

  void Node::updateComponents( const mb::Clock& clock )
  {
    for ( auto& comp : _components )
    {
      if ( comp.second->isEnabled( ) )
      {
        comp.second->update( clock );
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

  std::vector<Component*>Node::getComponentsByName( const std::string& name,
    bool includeInactive )
  {
    std::vector<Component*> cs;

    auto finds = _components.equal_range( name );

    for ( auto element = finds.first; element != finds.second; ++element )
    {
      if ( includeInactive || element->second->isEnabled( ) )
      {
        cs.push_back( element->second );
      }
    }
    return cs;
  }
}//NS
