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

#include "Matrix4.hpp"

namespace mb
{
  Matrix4::Matrix4( void )
  {
    this->_values = { {
      1.0f, 0.0f, 0.0f, 0.0f,
      0.0f, 1.0f, 0.0f, 0.0f,
      0.0f, 0.0f, 1.0f, 0.0f,
      0.0f, 0.0f, 0.0f, 1.0f,
    } };
  }

  Matrix4::Matrix4( const std::array<float, 16>& values )
  {
    this->_values = values;
  }

  void Matrix4::copy( const Matrix4& m )
  {
    this->_values = m._values;
  }

  void Matrix4::compose( const Vector3 &position,
    const Quaternion &quaternion, const Vector3 &scale )
  {
    /// ROTATION
    float x = quaternion.x( ),
      y = quaternion.y( ),
      z = quaternion.z( ),
      w = quaternion.w( );
    float x2 = x + x, y2 = y + y, z2 = z + z;
    float xx = x * x2, xy = x * y2, xz = x * z2;
    float yy = y * y2, yz = y * z2, zz = z * z2;
    float wx = w * x2, wy = w * y2, wz = w * z2;

    this->_values[ 0 ] = 1.0f - ( yy + zz );
    this->_values[ 4 ] = xy - wz;
    this->_values[ 8 ] = xz + wy;

    this->_values[ 1 ] = xy + wz;
    this->_values[ 5 ] = 1.0f - ( xx + zz );
    this->_values[ 9 ] = yz - wx;

    this->_values[ 2 ] = xz - wy;
    this->_values[ 6 ] = yz + wx;
    this->_values[ 10 ] = 1.0 - ( xx + yy );

    // last column
    this->_values[ 3 ] = 0.0f;
    this->_values[ 7 ] = 0.0f;
    this->_values[ 11 ] = 0.0f;

    // bottom row
    this->_values[ 12 ] = 0.0f;
    this->_values[ 13 ] = 0.0f;
    this->_values[ 14 ] = 0.0f;
    this->_values[ 15 ] = 1.0f;

    /// SCALE
    x = scale.x( );
    y = scale.y( );
    z = scale.z( );
    this->_values[ 0 ] *= x; this->_values[ 4 ] *= y; this->_values[ 8 ] *= z;
    this->_values[ 1 ] *= x; this->_values[ 5 ] *= y; this->_values[ 9 ] *= z;
    this->_values[ 2 ] *= x; this->_values[ 6 ] *= y; this->_values[ 10 ] *= z;
    this->_values[ 3 ] *= x; this->_values[ 7 ] *= y; this->_values[ 11 ] *= z;

    /// POSITION
    this->_values[ 12 ] = position.x( );
    this->_values[ 13 ] = position.y( );
    this->_values[ 14 ] = position.z( );
  }

  Matrix4
    Matrix4::perspective( const float& fovy_, const float& aspect,
    const float& near, const float& far )
  {

    float fovy = mb::Mathf::Deg2Rad * fovy_;

    float f = 1.0f / std::tan( fovy / 2.0f ), nf = 1.0f / ( near - far );

    std::array<float, 16> out;

    out[ 0 ] = f / aspect;
    out[ 1 ] = 0.0f;
    out[ 2 ] = 0.0f;
    out[ 3 ] = 0.0f;
    out[ 4 ] = 0.0f;
    out[ 5 ] = f;
    out[ 6 ] = 0.0f;
    out[ 7 ] = 0.0f;
    out[ 8 ] = 0.0f;
    out[ 9 ] = 0.0f;
    out[ 10 ] = ( far + near ) * nf;
    out[ 11 ] = -1.0f;
    out[ 12 ] = 0.0f;
    out[ 13 ] = 0.0f;
    out[ 14 ] = ( 2.0f * far * near ) * nf;
    out[ 15 ] = 0.0f;

    return Matrix4( out );
  }

  Matrix4
    Matrix4::orthographic( const float& left, const float& right,
    const float& bottom, const float& top,
    const float& near, const float& far )
  {
    float rl = ( right - left ), tb = ( top - bottom ), fn = ( far - left );
    std::array<float, 16> out;

    out[ 0 ] = 2.0f / rl;
    out[ 1 ] = 0.0f;
    out[ 2 ] = 0.0f;
    out[ 3 ] = 0.0f;
    out[ 4 ] = 0.0f;
    out[ 5 ] = 2.0f / tb;
    out[ 6 ] = 0.0f;
    out[ 7 ] = 0.0f;
    out[ 8 ] = 0.0f;
    out[ 9 ] = 0.0f;
    out[ 10 ] = -2.0f / fn;
    out[ 11 ] = 0.0f;
    out[ 12 ] = -( left + right ) / rl;
    out[ 13 ] = -( top + bottom ) / tb;
    out[ 14 ] = -( far + near ) / fn;
    out[ 15 ] = 1.0f;

    return Matrix4( out );
  }
}//NS

