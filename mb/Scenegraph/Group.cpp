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

#include "Group.hpp"
  #include <algorithm>
#include "../Exceptions/HasParentException.hpp"
#include "../Exceptions/RuntimeException.hpp"

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
  unsigned int Group::getNumChildren( void ) const
  {
    return _children.size( );
  }

  void Group::addChild( Node* node )
  {
    if ( node->parent( ) == this )
    {
      throw RuntimeException( "You trying to add this node repeated" );
    }
    if ( node->parent( ) != nullptr )
    {
      throw HasParentException( node->name( ),
        name( ), node->parent( )->name( ) );
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


  void Group::insertChild( unsigned int idx, Node* node )
  {
    _children.insert( _children.begin( ) + idx, node );
  }

  void Group::removeChild( unsigned int idx )
  {
    if ( _children.size( ) > idx )
    {
      _children.erase( _children.begin( ) + idx );
    }
  }

  void Group::forEachNode( std::function< void( Node * ) > callback )
  {
    std::for_each( _children.begin( ), _children.end( ), [&] ( Node* n )
    {
      if ( n->isEnabled( ) )
      {
        callback( n );
      }
    } );
  }
  void Group::accept( Visitor& v )
  {
    v.visitGroup( this );
  }
}
