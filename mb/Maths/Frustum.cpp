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

#include "Frustum.hpp"
#include <cmath>

namespace mb
{
  Frustum::Frustum( const float& fov, const float& ar,
    const float& near, const float& far )
  {
    _data[ FRUSTUM_UMAX ] = near * std::tan( 0.5f * fov * 3.1415f / 180.0f );
    _data[ FRUSTUM_RMAX ] = ar * _data[ FRUSTUM_UMAX ];
    _data[ FRUSTUM_UMIN ] = -_data[ FRUSTUM_UMAX ];
    _data[ FRUSTUM_RMIN ] = -_data[ FRUSTUM_RMAX ];
    _data[ FRUSTUM_DMIN ] = near;
    _data[ FRUSTUM_DMAX ] = far;
  }
}
