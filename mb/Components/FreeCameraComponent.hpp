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

#ifndef __MB_FREE_CAMERA_COMPONENT__
#define __MB_FREE_CAMERA_COMPONENT__

#include <mb/api.h>
#include "Component.hpp"
#include "../Maths/Vector3.hpp"
#include "../Maths/Quaternion.hpp"

namespace mb
{
  class FreeCameraComponent: public Component
  {
    IMPLEMENT_COMPONENT( FreeCameraComponent )
  public:
    MB_API
    virtual void start( void ) override;
    MB_API
    virtual void update( const mb::Clock& clock ) override;
  public:
    float fastMovementSpeed = 5.0f;
  protected:
    mb::Vector3 initPosition;
    mb::Quaternion initRotation;
  };
}

#endif /* __MB_FREE_CAMERA_COMPONENT__ */
