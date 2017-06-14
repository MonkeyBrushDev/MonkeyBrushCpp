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

#ifndef __MB_SPHERICAL__
#define __MB_SPHERICAL__

#include <mb/api.h>

#include "Vector3.hpp"

namespace mb
{
  class Spherical
  {
  public:
    MB_API
    mb::Vector3 toCartesian( void );
    MB_API
    static Spherical cartesianToSpherical( mb::Vector3 cartCoords );
    MB_API
    static mb::Vector3 sphericalToCartesian( float r, float p, float e );
  protected:
    float _radius;
    float _polar;
    float _elevation;
  };
}

#endif /* __MB_SPHERICAL__ */
