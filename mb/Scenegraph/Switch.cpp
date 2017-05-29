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

#include "Switch.hpp"

namespace mb
{
  Switch::Switch( const std::string name )
  : Group( name )
  , _currentIdx( 0 )
  {
  }

  Switch::~Switch( )
  {
    std::cout << "Destroy switch" << std::endl;
  }

  void Switch::forEachNode( std::function<void( Node* )> cb )
  {
    if ( !hasNodes( ) )
    {
      return;
    }
    Node* current = nodeAt( _currentIdx );
    if ( current != nullptr )
    {
      cb( current );
    }
  }

  void Switch::selectNextNode( void )
  {
    if ( !hasNodes( ) )
    {
      return;
    }
    _currentIdx = ( _currentIdx + 1 ) % getNumChildren( );
  }

  void Switch::selectPreviousNode( void )
  {
    if ( !hasNodes( ) )
    {
      return;
    }
    unsigned int nChildren = getNumChildren( );
    _currentIdx = ( _currentIdx + nChildren - 1 ) % nChildren;
  }

  Node* Switch::currentNode( void )
  {
    return nodeAt( _currentIdx );
  }

  unsigned int Switch::getCurrentNodeIndex( void ) const
  {
    return _currentIdx;
  }

  void Switch::setCurrentNodeIndex( unsigned int idx )
  {
    _currentIdx = idx;
  }
}
