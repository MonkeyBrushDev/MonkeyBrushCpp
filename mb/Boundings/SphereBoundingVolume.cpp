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

#include "SphereBoundingVolume.hpp"

namespace mb
{
  SphereBoundingVolume::SphereBoundingVolume( void )
    : _sphere( Vector3::ZERO, 1.0f )
  {
  }
  SphereBoundingVolume::SphereBoundingVolume( const Vector3& center, float radius )
    : _sphere( center, radius )
  {
  }
  SphereBoundingVolume::SphereBoundingVolume( const Sphere& sphere )
    : _sphere( sphere )
  {
  }
  const Vector3& SphereBoundingVolume::getCenter( void ) const
  {
    return _sphere.getCenter( );
  }
  float SphereBoundingVolume::getRadius( void ) const
  {
    return _sphere.getRadius( );
  }
  bool SphereBoundingVolume::contains( const Vector3& point )
  {
    float centerDiffSqr = ( _sphere.getCenter( ) - point ).getSquaredMagnitude( );
    float radiusSqr = _sphere.getRadius( ) * _sphere.getRadius( );
    return ( centerDiffSqr < radiusSqr );
  }
  void SphereBoundingVolume::computeFrom( const BoundingVolume* )
  {
    //computeFrom( volume->getCenter() + 
    //  volume->getMin(), volume->getCenter() + volume->getMax() );
  }
  void SphereBoundingVolume::expand( const std::vector<Vector3>& points )
  {
    if ( points.empty( ) )
    {
      _sphere.setCenter( Vector3::ZERO );
      _sphere.setRadius( 0.0f );
    }
    else
    {
      Vector3 max = points.front( );
      Vector3 min = points.front( );
      for ( const auto p : points )
      {
        if ( p[ 0 ] > max[ 0 ] ) max[ 0 ] = p[ 0 ];
        if ( p[ 1 ] > max[ 1 ] ) max[ 1 ] = p[ 1 ];
        if ( p[ 2 ] > max[ 2 ] ) max[ 2 ] = p[ 2 ];

        if ( p[ 0 ] < min[ 0 ] ) min[ 0 ] = p[ 0 ];
        if ( p[ 1 ] < min[ 1 ] ) min[ 1 ] = p[ 1 ];
        if ( p[ 2 ] < min[ 2 ] ) min[ 2 ] = p[ 2 ];
      }
      expand( min );
      expand( max );
    }
  }
  void SphereBoundingVolume::expand( const BoundingVolume *input )
  {
    _sphere.expand( Sphere( input->getCenter(), input->getRadius() ) );

    setMin( -getRadius() * Vector3::ONE );
    setMax(  getRadius() * Vector3::ONE );
  }
  void SphereBoundingVolume::expand( const Vector3& point )
  {
    _sphere.expand( Sphere( point, 0.0f ) );
    setMin( -getRadius( ) * Vector3::ONE );
    setMax(  getRadius( ) * Vector3::ONE );
  }
  int SphereBoundingVolume::intersect( const Plane& plane ) const
  {
    return _sphere.intersectPlane( plane );
  }
}