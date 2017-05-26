#ifndef __MB_VECTOR3__
#define __MB_VECTOR3__

#include <array>
#include "Mathf.hpp"
#include <cmath>
#include "Vector4.hpp"
#include <iomanip>
#include <iostream>

namespace mb
{
  class Vector3
  {
  public:
    Vector3( void )
      : Vector3( 0.0f )
    {
    }
    Vector3( const Vector4& v )
    {
      for ( unsigned int i = 0; i < 3; ++i )
      {
        _data[ i ] = v[ i ];
      }
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
    float getSquaredMagnitude( void ) const
    {
      //return ( *this ) * ( *this );
      return this->_data[ 0 ] * this->_data[ 0 ] +
        this->_data[ 1 ] * this->_data[ 1 ] +
        this->_data[ 2 ] * this->_data[ 2 ];
    }
    double getMagnitude( void ) const
    {
      return std::sqrt( getSquaredMagnitude( ) );
    }
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
    friend Vector3 operator-( const Vector3& u ) 
    {
      Vector3 result;
      result._data[ 0 ] = -u._data[ 0 ];
      result._data[ 1 ] = -u._data[ 1 ];
      result._data[ 2 ] = -u._data[ 2 ];
      return result;
    }
    friend Vector3 operator+( const Vector3& u, const Vector3& v )
    {
      return Vector3(
        u.x( ) + v.x( ),
        u.y( ) + v.y( ),
        u.z( ) + v.z( )
      );
    }
    friend Vector3 operator-( const Vector3& u, const Vector3& v )
    {
      return Vector3(
        u.x( ) - v.x( ),
        u.y( ) - v.y( ),
        u.z( ) - v.z( )
      );
    }
    friend Vector3 operator*( const Vector3& u, float v )
    {
      return Vector3(
        u.x( ) * v,
        u.y( ) * v,
        u.z( ) * v
      );
    }
    friend Vector3 operator*( float u, const Vector3& v )
    {
      return v * u;
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
    friend float operator*( const Vector3& u, const Vector3& v )
    {
      return u._data[ 0 ] * v._data[ 0 ] +
        u._data[ 1 ] * v._data[ 1 ] +
        u._data[ 2 ] * v._data[ 2 ];
    }
    friend Vector3& operator+=( Vector3& u, const Vector3& v )
    {
      u._data[ 0 ] += v._data[ 0 ];
      u._data[ 1 ] += v._data[ 1 ];
      u._data[ 2 ] += v._data[ 2 ];
      return u;
    }
    friend Vector3& operator-=( Vector3& u, const Vector3& v )
    {
      u._data[ 0 ] -= v._data[ 0 ];
      u._data[ 1 ] -= v._data[ 1 ];
      u._data[ 2 ] -= v._data[ 2 ];
      return u;
    }
    friend Vector3& operator*=( Vector3& u, float v )
    {
      u._data[ 0 ] *= v;
      u._data[ 1 ] *= v;
      u._data[ 2 ] *= v;
      return u;
    }
    friend Vector3& operator*=( float v, Vector3& u )
    {
      u._data[ 0 ] *= v;
      u._data[ 1 ] *= v;
      u._data[ 2 ] *= v;
      return u;
    }
    friend Vector3& operator/=( Vector3& u, float v )
    {
      float invV = 1.0f / v;

      u._data[ 0 ] *= invV;
      u._data[ 1 ] *= invV;
      u._data[ 2 ] *= invV;
      return u;
    }
    /// Cross product
    friend Vector3 operator^( const Vector3& u, const Vector3& v )
    {
      return Vector3(
        u._data[ 1 ] * v._data[ 2 ] - u._data[ 2 ] * v._data[ 1 ],
        u._data[ 2 ] * v._data[ 0 ] - u._data[ 0 ] * v._data[ 2 ],
        u._data[ 0 ] * v._data[ 1 ] - u._data[ 1 ] * v._data[ 0 ]
      );
    }
    static Vector3 cross( const Vector3&u, const Vector3& v )
    {
      return u ^ v;
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
          from.getNormalized( ), to.getNormalized( ) ), 
          -1.0f, 1.0f)) * 57.29578f;
    }

    friend std::ostream& operator<<( std::ostream &out, const Vector3& v )
    {
      out << std::setiosflags( std::ios::fixed | std::ios::showpoint )
        << std::setprecision( 10 );
      out << "(" << v[ 0 ];
      for ( unsigned int i = 1; i < 3; ++i )
      {
        out << ", " << v[ i ];
      }
      out << ")";
      return out;
    }
    MB_API
    static const Vector3 ZERO;
    MB_API
    static const Vector3 ONE;
    MB_API
    static const Vector3 FORWARD;
    MB_API
    static const Vector3 BACK;
    MB_API
    static const Vector3 UP;
    MB_API
    static const Vector3 DOWN;
    MB_API
    static const Vector3 LEFT;
    MB_API
    static const Vector3 RIGHT;
  protected:
    std::array< float, 3 > _data;
  };
}

#endif /* __MB_VECTOR3__ */
