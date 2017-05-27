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
  //  : _sphere( Vector3::ZERO, 1.0f )
  {
    // TODO
  }
  BoundingVolume* BoxBoundingVolume::clone( void )
  {
    // TODO
    return nullptr;
  }
  const Vector3& BoxBoundingVolume::getCenter( void ) const
  {
    // TODO
    return Vector3::ZERO;
  }
  float BoxBoundingVolume::getRadius( void ) const
  {
    // TODO
    return 0.0f;
  }
  bool BoxBoundingVolume::contains( const Vector3& point )
  {
    // TODO
    return false;
  }
  void BoxBoundingVolume::computeFrom( const BoundingVolume* )
  {
    // TODO
  }
  void BoxBoundingVolume::expand( const std::vector<Vector3>& )
  {
    // TODO
  }
  void BoxBoundingVolume::expand( const BoundingVolume* )
  {
    // TODO
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