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

#include "Ray.hpp"
#include "../Boundings/BoundingVolume.hpp"

namespace mb
{
  Ray::Ray( const Vector3& origin, const Vector3& direction )
    : _origin( origin )
    , _direction( direction )
  {
  }
  Vector3 Ray::origin( void ) const
  {
    return this->_origin;
  }
  Vector3 Ray::direction( void ) const
  {
    return this->_direction;
  }
  void Ray::origin( const Vector3& ori )
  {
    this->_origin = ori;
  }
  void Ray::direction( const Vector3& dir )
  {
    this->_direction = dir;
  }
  Vector3 Ray::getPoint( const float& t )
  {
    return Vector3(
      this->_origin.x( ) + t * this->_direction.x( ),
      this->_origin.y( ) + t * this->_direction.y( ),
      this->_origin.z( ) + t * this->_direction.z( )
    );
  }
  bool Ray::intersect( const BoundingVolume* )
  {
    // TODO
    return true;
  }
}
