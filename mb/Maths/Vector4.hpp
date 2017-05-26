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

#ifndef __MB_VECTOR4__
#define __MB_VECTOR4__

#include <array>
#include "Mathf.hpp"

namespace mb
{
  class Vector4
  {
  public:
    Vector4( void )
      : Vector4( 0.0f )
    {
    }
    explicit Vector4( float v )
    {
      for( unsigned int i = 0; i < 4; ++i )
      {
        _data[ i ] = v;
      }
    }
    Vector4( const Vector4& u )
    {
      std::copy( std::begin( u._data ), std::end( u._data ), std::begin( _data ) );
    }
    Vector4( float x, float y, float z, float w )
    {
      _data[ 0 ] = x;
      _data[ 1 ] = y;
      _data[ 2 ] = z;
      _data[ 3 ] = w;
    }

		float operator[]( unsigned int i ) const { return _data[ i ]; }
		float &operator[]( unsigned int i ) { return _data[ i ]; }

    float x( void ) const { return _data[ 0 ]; }
    float y( void ) const { return _data[ 1 ]; }
    float z( void ) const { return _data[ 2 ]; }
    float w( void ) const { return _data[ 3 ]; }
    float& x( void ) { return _data[ 0 ]; }
    float& y( void ) { return _data[ 1 ]; }
    float& z( void ) { return _data[ 2 ]; }
    float& w( void ) { return _data[ 3 ]; }
  public:
    bool operator==( const Vector4& v ) const
    {
      return std::equal( _data.begin( ), _data.end( ), v._data.begin( ) );
    }

    bool operator!=( const Vector4& v ) const
    {
      return !( *this == v );
    }
    Vector4& operator=( const Vector4& u )
    {
      std::copy( std::begin( u._data ), std::end( u._data ), std::begin( _data ) );
      return *this;
    }
    friend Vector4 operator+( const Vector4& u, const Vector4& v )
    {
      return Vector4(
        u.x( ) + v.x( ),
        u.y( ) + v.y( ),
        u.z( ) + v.z( ),
        u.w( ) + v.w( )
      );
    }
    friend Vector4& operator+=( Vector4& u, const Vector4& v )
    {
      u._data[ 0 ] += v._data[ 0 ];
      u._data[ 1 ] += v._data[ 1 ];
      u._data[ 2 ] += v._data[ 2 ];
      u._data[ 3 ] += v._data[ 3 ];
      return u;
    }
    friend Vector4 operator-( const Vector4& u, const Vector4& v )
    {
      return Vector4(
        u.x( ) - v.x( ),
        u.y( ) - v.y( ),
        u.z( ) - v.z( ),
        u.w( ) - v.w( )
      );
    }
    friend Vector4& operator-=( Vector4& u, const Vector4& v )
    {
      u._data[ 0 ] -= v._data[ 0 ];
      u._data[ 1 ] -= v._data[ 1 ];
      u._data[ 2 ] -= v._data[ 2 ];
      u._data[ 3 ] -= v._data[ 3 ];
      return u;
    }
    friend Vector4 operator*( const Vector4& u, const Vector4& v )
    {
      return Vector4(
        u.x( ) * v.x( ),
        u.y( ) * v.y( ),
        u.z( ) * v.z( ),
        u.w( ) * v.w( )
      );
    }
    friend Vector4& operator*=( Vector4& u, const Vector4& v )
    {
      u._data[ 0 ] *= v._data[ 0 ];
      u._data[ 1 ] *= v._data[ 1 ];
      u._data[ 2 ] *= v._data[ 2 ];
      u._data[ 3 ] *= v._data[ 3 ];
      return u;
    }
    friend Vector4 operator*( const Vector4& u, float v )
    {
      return Vector4(
        u.x( ) * v,
        u.y( ) * v,
        u.z( ) * v,
        u.w( ) * v
        );
    }
    friend Vector4 operator*( float v, const Vector4& u )
    {
      return u * v;
    }
    /*friend float operator*( const Vector4& u, const Vector4& v )
    {
      return u._data[ 0 ] * v._data[ 0 ] +
           u._data[ 1 ] * v._data[ 1 ] +
           u._data[ 2 ] * v._data[ 2 ] +
           u._data[ 3 ] * v._data[ 3 ];
    }*/
    friend Vector4& operator*=( Vector4& u, float v )
    {
      u._data[ 0 ] *= v;
      u._data[ 1 ] *= v;
      u._data[ 2 ] *= v;
      u._data[ 3 ] *= v;
      return u;
    }
    friend Vector4 operator/( const Vector4& u, float v )
    {
      float invV = 1.0f / v;

      return Vector4(
        u.x( ) * invV,
        u.y( ) * invV,
        u.z( ) * invV,
        u.w( ) * invV
      );
    }
    friend Vector4& operator/=( Vector4& u, float v )
    {
      float invV = 1.0f / v;

      u._data[ 0 ] *= invV;
      u._data[ 1 ] *= invV;
      u._data[ 2 ] *= invV;
      u._data[ 3 ] *= invV;
      return u;
    }
    float length( void ) const
    {
      return std::sqrt( squaredLength( ) );
    }
    float squaredLength( void ) const
    {
      float
        x = this->x( ),
        y = this->y( ),
        z = this->z( ),
        w = this->w( );

      return ( x * x + y * y + z * z + w * w );
    }
    Vector4 getNormalized( void ) const
    {
      float l = length( );
      if ( l == 1.0f )
      {
        return *this;
      }
      if ( l == 0.0f )
      {
        return Vector4( 0.0f );
      }
      return ( *this / l );
    }
    Vector4& normalize( void )
    {
      *this /= length( );
      return *this;
    }
    static float dot( const Vector4& lhs,  const Vector4& rhs )
    {
      return lhs.x( ) * rhs.x( ) +
             lhs.y( ) * rhs.y( ) +
             lhs.z( ) * rhs.z( ) +
             lhs.w( ) * rhs.w( );
    }
    static Vector4 reflect( const Vector4& inDirection,
      const Vector4& inNormal)
    {
      return -2.0f * Vector4::dot(inNormal, inDirection)
        * inNormal + inDirection;
    }
    static float angle( const Vector4& from, const Vector4& to )
    {
      return std::acos(Mathf::clamp(Vector4::dot(
          from.getNormalized( ), to.getNormalized( ) ), -1.0f, 1.0f)) * 57.29578f;
    }
  protected:
    std::array< float, 4 > _data;
  };
}

#endif /* __MB_VECTOR4__ */
