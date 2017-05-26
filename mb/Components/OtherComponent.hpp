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

#ifndef __MB_ORBIT_CAMERA__
#define __MB_ORBIT_CAMERA__

#include "Component.hpp"
#include <mb/api.h>

namespace mb
{
  class OtherComponent : public Component
  {
    IMPLEMENT_COMPONENT( OtherComponent )
  public:
    MB_API
    OtherComponent( );
    MB_API
    virtual ~OtherComponent( );
  };
}

#endif /* __MB_ORBIT_CAMERA__ */
