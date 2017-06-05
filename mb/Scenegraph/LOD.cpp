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

#include "LOD.hpp"

namespace mb
{
  LOD::LOD( const std::string& name )
    : Switch( name )
  {
  }
  void LOD::addChild( Node* node )
  {
    Switch::addChild( node );
    unsigned int numChildren = this->getNumChildren( );
    if ( numChildren > _rangeList.size( ) )
    {
      float maxRange = !_rangeList.empty( ) ? _rangeList.back( ).second : 0.0f;
      _rangeList.resize( numChildren, MinMaxPair( maxRange, maxRange ) );
    }
  }
  void LOD::addChild( Node* node, const float& min, const float& max )
  {
    Switch::addChild( node );
    unsigned int numChildren = this->getNumChildren( );
    if ( numChildren > _rangeList.size( ) )
    {
      _rangeList.resize( _children.size( ), MinMaxPair( min, min ) );
    }
    --numChildren;
    _rangeList[ numChildren ].first = min;
    _rangeList[ numChildren ].second = max;
  }

  void LOD::removeChild( Node* node )
  {
    unsigned int pos = std::find( _children.begin( ), _children.end( ), node )
      - _children.begin( );

    if ( pos < _rangeList.size() )
    {
      _rangeList.erase( _rangeList.begin( ) + pos );
    }
    Switch::removeChild( node );
  }
  void LOD::removeChildren( void )
  {
    _rangeList.clear( );
    Switch::removeChildren( );
  }
}
