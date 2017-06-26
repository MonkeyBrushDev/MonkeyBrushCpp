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

#include "LodNode.hpp"
#include "Camera.hpp"

namespace mb
{
  LodNode::LodNode( unsigned int numLOD )
    : Switch( "LODNODE" )
    , _numLevelsOfDetail( numLOD )
  {
    _localMinDist.reserve( numLOD );
    _localMaxDist.reserve( numLOD );
    _worldMinDist.reserve( numLOD );
    _worldMaxDist.reserve( numLOD );
  }
  LodNode::~LodNode( void )
  {
    _localMinDist.clear( );
    _localMaxDist.clear( );
    _worldMinDist.clear( );
    _worldMaxDist.clear( );
  }
  void LodNode::setLOD( const Camera* camera )
  {
    Matrix4 m = getWorld( ).computeModel( );
    _worldLodCenter = m * _localLodCenter;

    for ( int i = 0; i < _numLevelsOfDetail; ++i )
    {
      _worldMinDist[ i ] = getWorld( ).getScale( )[ 0 ] * _localMinDist[ i ];
      _worldMaxDist[ i ] = getWorld( ).getScale( )[ 0 ] * _localMaxDist[ i ];
    }

    setActiveChild( SW_INVALID_CHILD );
    Vector3 diff = _worldLodCenter - camera->getWorld( ).getPosition( );
    float dist = diff.length( );
    for ( int i = 0; i < _numLevelsOfDetail; ++i )
    {
      if ( _worldMinDist.at( i ) <= dist && dist < _worldMaxDist.at( i ) )
      {
        setActiveChild( i );
        break;
      }
    }
  }
}
