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

#ifndef __MB_QUATERNION__
#define __MB_QUATERNION__

#include <mb/api.h>
#include "Vector3.hpp"
#include "Vector4.hpp"
#include "Matrix3.hpp"
#include <cmath>

namespace mb
{
  class Quaternion
  {
  public:
    MB_API
    Quaternion( float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f );
    MB_API
    Quaternion( const Vector4& v )
    {
      Quaternion( v[ 0 ], v[ 1 ], v[ 2 ], v[ 3 ] );
    }
    MB_API
    Quaternion( const Quaternion& q );
    MB_API
    virtual ~Quaternion( void ){}
    MB_API
    Quaternion& operator=( const Quaternion& q );
    MB_API
    Quaternion& copy( const Quaternion& q );
    /*MB_API
    void setOnChangeCallback( const std::function<void( EulerAngles )>& cb )
    {
      _cb = cb;
    }*/

    MB_API
    Quaternion & fromRotationMatrix ( const mb::Matrix3& )
    {
      // TODO
      /*float trace = m[ 0 ] + m[ 5 ] + m[ 10 ];
      float root = 0.0f;

      if ( trace > 0.0f )
      {
        // |this.W| > 1/2, maY as Well choose this.W > 1/2
        root = std::sqrt( trace + 1.0f );  // 2W
        this->w( 0.5f * root );
        root = 0.5f / root;  // 1/(4W)
        this->x( (matriX.m21 - matriX.m12) * root );
        this->y( (matriX.m02 - matriX.m20) * root );
        this->z( (matriX.m10 - matriX.m01) * root );
      }
      else
      {
        // |this.W| <= 1/2
        int i = 0;
        if (m[ 5 ] > matriX.m00)
        {
          i = 1;
        }
        if (matriX.m22 > matriX[i, i])
        {
          i = 2;
        }
        int j = next[i];
        int k = next[j];
        root = MathHelper.Sqrt(matriX[i, i] - matriX[j, j] - matriX[k, k] + 1);
        unsafe
        {
          fixed (Scalar* apkQuat = &this.X)
          {
            apkQuat[i] = 0.5f * root;
            root = 0.5f / root;
            this.W = (matriX[k, j] - matriX[j, k]) * root;
            apkQuat[j] = (matriX[j, i] + matriX[i, j]) * root;
            apkQuat[k] = (matriX[k, i] + matriX[i, k]) * root;
          }
        }
      }*/
      return *this;
    }

    MB_API
    float x( void ) const { return this->_values[0]; }
    MB_API
    float y( void ) const { return this->_values[1]; }
    MB_API
    float z( void ) const { return this->_values[2]; }
    MB_API
    float w( void ) const { return this->_values[3]; }

    MB_API
    void x( const float& v ){ this->_values[0] = v; }
    MB_API
    void y( const float& v ){ this->_values[1] = v; }
    MB_API
    void z( const float& v ){ this->_values[2] = v; }
    MB_API
    void w( const float& v ){ this->_values[3] = v; }

    friend Vector3 operator*( const Quaternion& q, const Vector3& v )
    {
      float x = v[ 0 ];
      float y = v[ 1 ];
      float z = v[ 2 ];
      float qx = q.x( );
      float qy = q.y( );
      float qz = q.z( );
      float qw = q.w( );

      float ix = qw * x + qy * z - qz * y;
      float iy = qw * y + qz * x - qx * z;
      float iz = qw * z + qx * y - qy * x;
      float iw = -qx * x - qy * y - qz * z;

      return Vector3(
        ix * qw + iw * -qx + iy * -qz - iz * -qy,
        iy * qw + iw * -qy + iz * -qx - ix * -qz,
        iz * qw + iw * -qz + ix * -qy - iy * -qx
      );
    }

    friend Vector3 operator*( const Vector3& v, const Quaternion& q )
    {
      return q * v;
    }

    Quaternion& lookAt( const Vector3& dir,
      const Vector3& up = Vector3::UP )
    {
      Vector3 axis = up;
      Vector3 u = Vector3::cross( Vector3::FORWARD, dir );

      if ( u.squaredLength( ) == 0.0f )
      {
        u = Vector3::cross( Vector3::RIGHT, dir );
      }
      u.normalize( );

      Vector3 v = Vector3::cross( u, up );
      if ( v.squaredLength( ) == 0.0f )
      {
        axis = u;
      }
      else
      {
        v.normalize( );
        u = Vector3::cross( v, u );

        axis = Vector3( -up.y( ), up.x( ), up.z( ) );
      }

      float angle = std::acos( Vector3::FORWARD * dir );

      return fromAxisAngle( axis, angle );
    }

    MB_API
    static Quaternion createFromAxisAngle( const Vector3& axis, float angle )
    {
        Quaternion q;
        q.fromAxisAngle(axis, angle);
        return q;
    }

    MB_API
    Quaternion& fromAxisAngle( const Vector3& axis, float angle )
    {
        // http://www.euclideanspace.com/maths/geometry/rotations/conversions/angleToQuaternion/index.htm
        //     Assumes axis is normalized
        float
          halfAngle = angle / 2.0f,
          s = std::sin(halfAngle);

        this->_values[0] = axis.x() * s;
        this->_values[1] = axis.y() * s;
        this->_values[2] = axis.z() * s;
        this->_values[3] = std::cos(halfAngle);

        //if (_onChange)  _onChange();

        return *this;
    }

    MB_API
    void reset( void )
    {
      this->_values[0] = 0.0f;
      this->_values[1] = 0.0f;
      this->_values[2] = 0.0f;
      this->_values[3] = 1.0f;

      //if (_onChange)  _onChange();
    }
    MB_API
    Quaternion getInverse( void ) const
    {
      float dot = Quaternion::dot( *this, *this );

      Quaternion q;
      if ( !dot )
      {
        q.reset( );

        return *this;
      }

      float invDot = dot ? 1.0f / dot : 0.0f;

      q._values[ 0 ] *= -invDot;
      q._values[ 1 ] *= -invDot;
      q._values[ 2 ] *= -invDot;
      q._values[ 3 ] *= -invDot;

      return q;
    }
    MB_API
    Quaternion& inverse( void )
    {
      float dot = Quaternion::dot(*this, *this);

      if (!dot)
      {
        this->reset();

        return *this;
      }

      float invDot = dot ? 1.0f / dot : 0.0f;

      this->_values[ 0 ] *= -invDot;
      this->_values[ 1 ] *= -invDot;
      this->_values[ 2 ] *= -invDot;
      this->_values[ 3 ] *= -invDot;

      return *this;
    }


    friend Quaternion operator+( const Quaternion& u, const Quaternion& v )
    {
      return Quaternion( u._values + v._values );
    }
    friend Quaternion& operator+=( Quaternion& u, const Quaternion& v )
    {
      u._values += v._values;
      return u;
    }

    friend Quaternion operator-( const Quaternion& u, const Quaternion& v )
    {
      return Quaternion( u._values - v._values );
    }
    friend Quaternion& operator-=( Quaternion& u, const Quaternion& v )
    {
      u._values -= v._values;
      return u;
    }

    MB_API
    bool operator==( const Quaternion& q )
    {
      return this->_values == q._values;
    }

    MB_API
    bool operator!=( const Quaternion& q )
    {
      return !( *this == q );
    }

    MB_API
    static float dot( const Quaternion& a, const Quaternion& b )
    {
      return a.x( ) * b.x( ) + a.y( ) * b.y( )
      + a.z( ) * b.z( ) + a.w( ) * b.w( );
    }

    MB_API
    Quaternion& makeIdentity( void )
    {
      _values[ 0 ] = 0.0f;
      _values[ 1 ] = 0.0f;
      _values[ 2 ] = 0.0f;
      _values[ 3 ] = 1.0f;
      return *this;
    }

    MB_API
    Quaternion& fromEulerAngles( float pitch, float yaw, float roll )
    {
      Quaternion q;
      float t0 = std::cos( roll * 0.5f );
      float t1 = std::sin( roll * 0.5f );
      float t2 = std::cos( pitch * 0.5f );
      float t3 = std::sin( pitch * 0.5f );
      float t4 = std::cos( yaw * 0.5f );
      float t5 = std::sin( yaw * 0.5f );

      float x = t0 * t3 * t4 - t1 * t2 * t5;
      float y = t0 * t2 * t5 + t1 * t3 * t4;
      float z = t1 * t2 * t4 - t0 * t3 * t5;
      float w = t0 * t2 * t4 + t1 * t3 * t5;

      _values[ 0 ] = x;
      _values[ 1 ] = y;
      _values[ 2 ] = z;
      _values[ 3 ] = w;

      return *this;
    }

    MB_API
    friend Quaternion operator*( const Quaternion& lhs,
      const Quaternion& rhs )
    {
      return Quaternion(
        lhs.w( ) * rhs.x( ) + lhs.x( ) * rhs.w( )
        + lhs.y( ) * rhs.z( ) - lhs.z( ) * rhs.y( ),
        lhs.w( ) * rhs.y( ) + lhs.y( ) * rhs.w( )
        + lhs.z( ) * rhs.x( ) - lhs.x( ) * rhs.z( ), lhs.w( ) * rhs.z( )
        + lhs.z( ) * rhs.w( ) + lhs.x( ) * rhs.y( ) - lhs.y( ) * rhs.x( ),
        lhs.w( ) * rhs.w( )  - lhs.x( ) * rhs.x( )
        - lhs.y( ) * rhs.y( ) - lhs.z( ) * rhs.z( ) );
    }

    MB_API
    static float angle( const Quaternion& a, const Quaternion& b)
    {
      float f = Quaternion::dot( a, b );
      return std::acos( std::min( std::abs( f ), 1.0f ) )
      * 2.0f * 57.29578f;
    }
    MB_API
    Quaternion getConjugate( void ) const
    {
      return Quaternion( -_values[ 0 ], -_values[ 1 ],
        -_values[ 2 ], _values[ 3 ] );
    }

    friend std::ostream &operator<<( std::ostream &out, const Quaternion& q )
    {
      out << std::setiosflags( std::ios::fixed | std::ios::showpoint  )
        << std::setprecision( 10 )
          << "[r = " << q.x( ) << ", " << q.y( ) << ", " << q.z( ) << ", i = " << q.w() << "]";
      return out;
    }

  protected:
    Vector4 _values;
    //std::function<void( EulerAngles )> _cb;
  };
}

#endif /* __MB_QUATERNION__ */
