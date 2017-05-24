#ifndef __MB_QUATERNION__
#define __MB_QUATERNION__

#include <array>
#include <mb/api.h>
#include "Vector3.hpp"
#include "Vector4.hpp"

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

    MB_API
    Quaternion& fromAxisAngle( const Vector3& axis, float angle )
    {
      float sinTheta = std::sin( 0.5f * angle );
      float cosTheta = std::cos( 0.5f * angle );

      _values[ 0 ] = axis[ 0 ] * sinTheta;
      _values[ 1 ] = axis[ 1 ] * sinTheta;
      _values[ 2 ] = axis[ 2 ] * sinTheta;
      _values[ 3 ] = cosTheta;

      return *this;
    }

    MB_API
    void reset()
    {
      this->_values[0] = 0.0f;
      this->_values[1] = 0.0f;
      this->_values[2] = 0.0f;
      this->_values[3] = 1.0f;

      //if (_onChange)  _onChange();
    }
    MB_API
    Quaternion& setFromAxisAngle(const Vector3& axis, float angle)
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
    Quaternion& inverse()
    {
      float dot = Quaternion::dot(*this, *this);

      if (!dot)
      {
        this->reset();

        return *this;
      }

      float invDot = dot ? 1.0f / dot : 0.0f;

      this->_values[0] *= -invDot;
      this->_values[1] *= -invDot;
      this->_values[2] *= -invDot;
      this->_values[3] *= -invDot;

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
      return a.x( ) * b.x( ) + a.y( ) * b.y( ) + a.z( ) * b.z( ) + a.w( ) * b.w( );
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
    friend Quaternion& operator*( const Quaternion& lhs, const Quaternion& rhs )
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
      return std::acos( std::min( std::abs( f ), 1.0f ) ) * 2.0f * 57.29578f;
    }
    MB_API
    Quaternion getConjugate( void ) const
    {
      return Quaternion( -_values[ 0 ], -_values[ 1 ], -_values[ 2 ], _values[ 3 ] );
    }
  protected:
    Vector4 _values;
    //std::function<void( EulerAngles )> _cb;
  };
}

#endif /* __MB_QUATERNION__ */
