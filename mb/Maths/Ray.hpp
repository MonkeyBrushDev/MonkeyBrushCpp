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

#ifndef __MB_RAY__
#define __MB_RAY__

#include <mb/api.h>

#include "Vector3.hpp"

namespace mb
{
  class BoundingVolume;
  class Ray
  {
  public:
    Ray(const Vector3& origin = Vector3( 0.0f ),
      const Vector3& direction = Vector3( 0.0f ) );
    MB_API
    Vector3 origin( void ) const;
    MB_API
    Vector3 direction( void ) const;
    MB_API
    void origin( const Vector3& ori );
    MB_API
    void direction( const Vector3& dir );
    MB_API
    Vector3 getPoint( const float& t );

    Ray &operator=( const Ray& r )
    {
      _origin = r._origin;
      _direction = r._direction;
      return *this;
    }
    bool operator==( const Ray& r )
    {
      return ( _origin == r._origin && _direction == r._direction );
    }

    bool operator!=( const Ray& r )
    {
      return !( *this == r );
    }

    bool intersect( const BoundingVolume* );
  protected:
    Vector3 _origin;
    Vector3 _direction;
  };
}

#endif /* __MB_RAY__ */
