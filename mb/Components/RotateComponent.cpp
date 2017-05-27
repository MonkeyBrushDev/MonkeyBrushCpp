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

#include "RotateComponent.hpp"
#include "../Scenegraph/Node.hpp"

namespace mb
{
  RotateComponent::RotateComponent( const Vector3& axis, float speed )
    : _axis( axis )
    ,  _speed( speed )
    , _time( 0.0f )
  {
  }
  void RotateComponent::update(const float &dt)
  {
    node()->local().rotate().fromAxisAngle( _axis, _time * 2.0f * mb::Mathf::PI );
    _time += _speed * dt;
  }
}
