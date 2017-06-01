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

#include "BoxBoundingVolume.hpp"

namespace mb
{
  BoxBoundingVolume::BoxBoundingVolume( void )
    : _sphere( Vector3::ZERO, 1.0f )
  {
    float cos45 = std::cos( 45.0f );
    setMin( -cos45 * getRadius( ) * mb::Vector3::ONE );
    setMax( cos45 * getRadius( ) * mb::Vector3::ONE );
  }
  BoundingVolume* BoxBoundingVolume::clone( void )
  {
    // TODO
    return nullptr;
  }
  const Vector3& BoxBoundingVolume::getCenter( void ) const
  {
    return _sphere.getCenter();
  }
  float BoxBoundingVolume::getRadius( void ) const
  {
    return _sphere.getRadius();
  }
  bool BoxBoundingVolume::contains( const Vector3& )
  {
    // TODO
    return false;
  }
  void BoxBoundingVolume::computeFrom( const BoundingVolume* bv )
  {
    auto min = bv->getCenter( ) + bv->getMin( );
    auto max = bv->getCenter( ) + bv->getMax( );
    _sphere.setCenter( 0.5f * ( max + min ) );
    _sphere.setRadius( std::max( 0.01f, ( max - _sphere.getCenter( ) ).getMagnitude( ) ) );

    setMin( min - getCenter( ) );
    setMax( max - getCenter( ) );
  }
  void BoxBoundingVolume::expand( const std::vector<Vector3>& positions )
  {
    mb::Vector3 max = positions.front( );
    mb::Vector3 min = positions.front( );

    for ( unsigned int i = 1, size = positions.size( ); i < size; ++i )
    {
      const Vector3 &pos = positions[ i ];

      if ( pos[ 0 ] > max[ 0 ] ) max[ 0 ] = pos[ 0 ];
      if ( pos[ 1 ] > max[ 1 ] ) max[ 1 ] = pos[ 1 ];
      if ( pos[ 2 ] > max[ 2 ] ) max[ 2 ] = pos[ 2 ];

      if ( pos[ 0 ] < min[ 0 ] ) min[ 0 ] = pos[ 0 ];
      if ( pos[ 1 ] < min[ 1 ] ) min[ 1 ] = pos[ 1 ];
      if ( pos[ 2 ] < min[ 2 ] ) min[ 2 ] = pos[ 2 ];
    }

    expand( max );
    expand( min );
  }
  void BoxBoundingVolume::expand( const BoundingVolume* bv )
  {
    expand( bv->getCenter( ) + bv->getMin( ) );
    expand( bv->getCenter( ) + bv->getMax( ) );
  }
  void BoxBoundingVolume::expand( const Vector3& )
  {
    // TODO
  }
  int BoxBoundingVolume::intersect( const Plane& ) const
  {
    // TODO
    return 0;
  }
}
