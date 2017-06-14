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

#include "Spherical.hpp"
#include "Mathf.hpp"
#include <float.h>

namespace mb
{
  mb::Vector3 Spherical::toCartesian( void )
  {
    return sphericalToCartesian(_radius, _polar, _elevation);
  }
  Spherical Spherical::cartesianToSpherical( mb::Vector3 cartCoords )
  {
    if ( cartCoords.x( ) == 0.0f )
    {
      cartCoords.x() = FLT_EPSILON;
    }
    Spherical res;
    res._radius = ( float) sqrt( ( cartCoords.x( ) * cartCoords.x( ) )
                + ( cartCoords.y( ) * cartCoords.y( ) )
                + ( cartCoords.z( ) * cartCoords.z( ) ) );
    res._polar = ( float ) atan(cartCoords.z( ) / cartCoords.x( ) );
    if ( cartCoords.x( ) < 0.0f )
    {
      res._polar += Mathf::PI;
    }
    res._elevation = ( float ) std::asin( cartCoords.y( ) / res._radius );
    return res;
  }
  mb::Vector3 Spherical::sphericalToCartesian( float r, float p, float e )
  {
    float a = ( float ) ( r * cos( e ) );
    return mb::Vector3(
      ( float ) ( a * cos( p ) ),
      ( float ) ( r * sin( e ) ),
      ( float ) ( a * sin( p ) )
    );
  }
}
