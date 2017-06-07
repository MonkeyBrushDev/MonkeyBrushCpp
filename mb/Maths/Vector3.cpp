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

#include "Vector3.hpp"

namespace mb
{
  const Vector3 Vector3::ZERO = Vector3( 0.0f );
  const Vector3 Vector3::ONE = Vector3(1.0f );
  const Vector3 Vector3::FORWARD = Vector3( 0.0f, 0.0f, 1.0f );
  const Vector3 Vector3::BACK = Vector3( 0.0f, 0.0f, -1.0f );
  const Vector3 Vector3::UP = Vector3( 0.0f, 1.0f, 0.0f );
  const Vector3 Vector3::DOWN = Vector3( 0.0f, -1.0f, 0.0f );
  const Vector3 Vector3::LEFT = Vector3( -1.0f, 0.0f, 0.0f );
  const Vector3 Vector3::RIGHT = Vector3( 1.0f, 0.0f, 0.0f );
  const Vector3 Vector3::X_AXIS = Vector3( 1.0f, 0.0f, 0.0f );
  const Vector3 Vector3::Y_AXIS = Vector3( 0.0f, 1.0f, 0.0f );
  const Vector3 Vector3::Z_AXIS = Vector3( 0.0f, 0.0f, 1.0f );
}
