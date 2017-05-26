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

#include "Quaternion.hpp"

namespace mb
{
  Quaternion::Quaternion( float x, float y, float z, float w )
  {
    this->_values[0] = x;
    this->_values[1] = y;
    this->_values[2] = z;
    this->_values[3] = w;
  }

  Quaternion::Quaternion( const Quaternion& q )
  {
    this->_values[0] = q.x();
    this->_values[1] = q.y();
    this->_values[2] = q.z();
    this->_values[3] = q.w();
  }

  Quaternion& Quaternion::operator=( const Quaternion& q )
  {
    return copy(q);
  }
  Quaternion& Quaternion::copy( const Quaternion& q )
  {
    x(q.x());
    y(q.y());
    z(q.z());
    w(q.w());
    return *this;
  }
}