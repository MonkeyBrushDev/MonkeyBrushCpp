#ifndef __MB_VECTOR3__
#define __MB_VECTOR3__

#include <array>
#include "Mathf.hpp"
#include <cmath>

namespace mb
{
  class Vector3
  {
  public:
    Vector3( void )
      : Vector3( 0.0f )
    {
    }
    explicit Vector3( float v )
    {
      for( unsigned int i = 0; i < 3; ++i )
      {
        _data[ i ] = v;
      }
    }
    Vector3( const Vector3& u )
    {
      std::copy( std::begin( u._data ), std::end( u._data ), std::begin( _data ) );
    }
    Vector3( float x, float y, float z )
    {
      _data[ 0 ] = x;
      _data[ 1 ] = y;
      _data[ 2 ] = z;
    }

		float operator[]( unsigned int i ) const { return _data[ i ]; }
		float &operator[]( unsigned int i ) { return _data[ i ]; }

    float x( void ) const { return _data[ 0 ]; }
    float y( void ) const { return _data[ 1 ]; }
    float z( void ) const { return _data[ 2 ]; }
    float& x( void ) { return _data[ 0 ]; }
    float& y( void ) { return _data[ 1 ]; }
    float& z( void ) { return _data[ 2 ]; }
  public:
    bool operator==( const Vector3& v ) const
    {
      return std::equal( _data.begin( ), _data.end( ), v._data.begin( ) );
    }

    bool operator!=( const Vector3& v ) const
    {
      return !( *this == v );
    }
    Vector3& operator=( const Vector3& u )
    {
      std::copy( std::begin( u._data ), std::end( u._data ), std::begin( _data ) );
      return *this;
    }
    friend Vector3 operator+( const Vector3& u, const Vector3& v )
    {
      return Vector3(
        u.x( ) + v.x( ),
        u.y( ) + v.y( ),
        u.z( ) + v.z( )
      );
    }
    friend Vector3& operator+=( Vector3& u, const Vector3& v )
    {
      u._data[ 0 ] += v._data[ 0 ];
      u._data[ 1 ] += v._data[ 1 ];
      u._data[ 2 ] += v._data[ 2 ];
      return u;
    }
    friend Vector3 operator-( const Vector3& u, const Vector3& v )
    {
      return Vector3(
        u.x( ) - v.x( ),
        u.y( ) - v.y( ),
        u.z( ) - v.z( )
      );
    }
    friend Vector3& operator-=( Vector3& u, const Vector3& v )
    {
      u._data[ 0 ] -= v._data[ 0 ];
      u._data[ 1 ] -= v._data[ 1 ];
      u._data[ 2 ] -= v._data[ 2 ];
      return u;
    }
    friend Vector3 operator*( const Vector3& u, const Vector3& v )
    {
      return Vector3(
        u.x( ) * v.x( ),
        u.y( ) * v.y( ),
        u.z( ) * v.z( )
      );
    }
    friend Vector3& operator*=( Vector3& u, const Vector3& v )
    {
      u._data[ 0 ] *= v._data[ 0 ];
      u._data[ 1 ] *= v._data[ 1 ];
      u._data[ 2 ] *= v._data[ 2 ];
      return u;
    }
    friend Vector3 operator*( const Vector3& u, float v )
    {
      return Vector3(
        u.x( ) * v,
        u.y( ) * v,
        u.z( ) * v
      );
    }
    friend Vector3 operator*( float v, const Vector3& u )
    {
      return u * v;
    }
    friend Vector3& operator*=( Vector3& u, float v )
    {
      u._data[ 0 ] *= v;
      u._data[ 1 ] *= v;
      u._data[ 2 ] *= v;
      return u;
    }
    friend Vector3 operator/( const Vector3& u, float v )
    {
      float invV = 1.0f / v;

      return Vector3(
        u.x( ) * invV,
        u.y( ) * invV,
        u.z( ) * invV
      );
    }
    friend Vector3& operator/=( Vector3& u, float v )
    {
      float invV = 1.0f / v;

      u._data[ 0 ] *= invV;
      u._data[ 1 ] *= invV;
      u._data[ 2 ] *= invV;
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
        z = this->z( );

      return ( x * x + y * y + z * z );
    }
    Vector3 getNormalized( void ) const
    {
      float l = length( );
      if ( l == 1.0f )
      {
        return *this;
      }
      if ( l == 0.0f )
      {
        return Vector3( 0.0f );
      }
      return ( *this / l );
    }
    Vector3& normalize( void )
    {
      *this /= length( );
      return *this;
    }
    static float dot( const Vector3& lhs,  const Vector3& rhs)
    {
      return lhs.x( ) * rhs.x( ) +
             lhs.y( ) * rhs.y( ) +
             lhs.z( ) * rhs.z( );
    }
    static Vector3 reflect( const Vector3& inDirection,
      const Vector3& inNormal)
    {
      return -2.0f * Vector3::dot(inNormal, inDirection)
        * inNormal + inDirection;
    }
    static float angle( const Vector3& from, const Vector3& to )
    {
      return std::acos(Mathf::clamp(Vector3::dot(
          from.getNormalized( ), to.getNormalized( ) ), -1.0f, 1.0f)) * 57.29578f;
    }
    static const Vector3 zero;
    static const Vector3 one;
    static const Vector3 forward;
    static const Vector3 back;
    static const Vector3 up;
    static const Vector3 down;
    static const Vector3 left;
    static const Vector3 right;
  protected:
    std::array< float, 3 > _data;
  };
}

#endif /* __MB_VECTOR3__ */
