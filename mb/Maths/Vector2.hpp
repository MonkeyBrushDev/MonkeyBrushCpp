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

#ifndef __MB_VECTOR2__
#define __MB_VECTOR2__

#include <array>

#include <mb/api.h>

#include <cmath>

namespace mb
{
  class Vector2
  {
  public:
    Vector2( void )
      : Vector2( 0.0f )
    {
    }
    explicit Vector2( float v )
    {
      for( unsigned int i = 0; i < 2; ++i )
      {
        _data[ i ] = v;
      }
    }
    Vector2( const Vector2& u )
    {
      std::copy( std::begin( u._data ), std::end( u._data ), std::begin( _data ) );
    }
    Vector2( float x, float y )
    {
      _data[ 0 ] = x;
      _data[ 1 ] = y;
    }

    float* data( void )
    {
      return _data.data( );
    }

		float operator[]( unsigned int i ) const { return _data[ i ]; }
		float &operator[]( unsigned int i ) { return _data[ i ]; }

    float x( void ) const { return _data[ 0 ]; }
    float y( void ) const { return _data[ 1 ]; }
    float& x( void ) { return _data[ 0 ]; }
    float& y( void ) { return _data[ 1 ]; }
  public:
    bool operator==( const Vector2& v ) const
    {
      return std::equal( _data.begin( ), _data.end( ), v._data.begin( ) );
    }

    bool operator!=( const Vector2& v ) const
    {
      return !( *this == v );
    }
    Vector2& operator=( const Vector2& u )
    {
      std::copy( std::begin( u._data ), std::end( u._data ), std::begin( _data ) );
      return *this;
    }
    friend Vector2 operator+( const Vector2& u, const Vector2& v )
    {
      return Vector2(
        u.x( ) + v.x( ),
        u.y( ) + v.y( )
      );
    }
    friend Vector2& operator+=( Vector2& u, const Vector2& v )
    {
      u._data[ 0 ] += v._data[ 0 ];
      u._data[ 1 ] += v._data[ 1 ];
      return u;
    }
    friend Vector2 operator-( const Vector2& u, const Vector2& v )
    {
      return Vector2(
        u.x( ) - v.x( ),
        u.y( ) - v.y( )
      );
    }
    friend Vector2& operator-=( Vector2& u, const Vector2& v )
    {
      u._data[ 0 ] -= v._data[ 0 ];
      u._data[ 1 ] -= v._data[ 1 ];
      return u;
    }
    friend Vector2 operator*( const Vector2& u, const Vector2& v )
    {
      return Vector2(
        u.x( ) * v.x( ),
        u.y( ) * v.y( )
      );
    }
    friend Vector2& operator*=( Vector2& u, const Vector2& v )
    {
      u._data[ 0 ] *= v._data[ 0 ];
      u._data[ 1 ] *= v._data[ 1 ];
      return u;
    }
    friend Vector2 operator*( const Vector2& u, float v )
    {
      return Vector2(
        u.x( ) * v,
        u.y( ) * v
      );
    }
    friend Vector2& operator*=( Vector2& u, float v )
    {
      u._data[ 0 ] *= v;
      u._data[ 1 ] *= v;
      return u;
    }
    friend Vector2 operator/( const Vector2& u, float v )
    {
      float invV = 1.0f / v;

      return Vector2(
        u.x( ) * invV,
        u.y( ) * invV
      );
    }
    friend Vector2& operator/=( Vector2& u, float v )
    {
      float invV = 1.0f / v;

      u._data[ 0 ] *= invV;
      u._data[ 1 ] *= invV;
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
        y = this->y( );

      return ( x * x + y * y );
    }
    Vector2 getNormalized( void ) const
    {
      float l = length( );
      if ( l == 1.0f )
      {
        return *this;
      }
      if ( l == 0.0f )
      {
        return Vector2( 0.0f );
      }
      return ( *this / l );
    }
    Vector2& normalize( void )
    {
      *this /= length( );
      return *this;
    }
  protected:
    std::array< float, 2 > _data;
  };
}

#endif /* __MB_VECTOR2__ */
