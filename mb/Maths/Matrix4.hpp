#ifndef WRAPPER_H
#define WRAPPER_H

#include <mb/api.h>
#include "Vector3.hpp"
#include "Vector4.hpp"
#include "Quaternion.hpp"

#include <vector>
#include <iostream>
#include <iomanip>

namespace mb
{

 class Matrix4
 {
  public:
    MB_API
    Matrix4( void );

    MB_API
    Matrix4( const std::array<float, 16>& values );

    MB_API
    void copy( const Matrix4& m );

    MB_API
    std::array<float, 16> values( void ) const { return _values; }

    MB_API
    void compose( const Vector3& position, const Quaternion& quaternion, const Vector3& scale );

    MB_API
    static Matrix4 perspective( const float& fovy, const float& aspect,
                             const float& near, const float& far );

    MB_API
    static Matrix4 orthographic( const float& left, const float& right,
                              const float& bottom, const float& top,
                              const float& near, const float& far );

    float operator[]( int i ) const
    {
      return _values[ i ];
    }

    float &operator[]( int i )
    {
      return _values[ i ];
    }

    friend std::ostream& operator<<( std::ostream &out, const Matrix4& m )
    {
      out << std::setiosflags( std::ios::fixed | std::ios::showpoint )
        << std::setprecision( 2 );
      out << "(";
      for ( unsigned int i = 0; i < 4; ++i )
      {
        for ( unsigned int j = 0; j < 4; ++j )
        {
          out << m[ i * 4 + j ];
          if ( j < 3 || i < 3 )
          {
            out << ", ";
          }
        }
        if ( i < 3 )
        {
          out << "\n";
        }
      }
      out << ")";
      return out;
    }
    MB_API
    Matrix4& makeIdentity( void )
    {
      for ( unsigned int i = 0; i < 4; ++i )
      {
        for ( unsigned int j = 0; j < 4; ++j )
        {
          if ( i == j ) { _values[ i * 4 + j ] = 1; }
          else { _values[ i * 4 + j ] = 0; }
        }
      }
      return *this;
    }
    MB_API
    Matrix4 getTranspose( void ) const
    {
      Matrix4 result;
      
      for ( unsigned int i = 0; i < 4; ++i )
      {
        for ( unsigned int j = 0; j < 4; ++j )
        {
          result._values[ j * 4 + i ] = _values[ i * 4 + j ];
        }
      }

      return result;
    }
    MB_API
    Matrix4 &makeInverse( void )
    {
        *this = getInverse();
        return *this;
    }
    MB_API
    Matrix4 getInverse( void ) const
    {
      Matrix4 result;

      float a00 = _values[ 0 ], a01 = _values[ 1 ], a02 = _values[ 2 ], a03 = _values[ 3 ],
        a10 = _values[ 4 ], a11 = _values[ 5 ], a12 = _values[ 6 ], a13 = _values[ 7 ],
        a20 = _values[ 8 ], a21 = _values[ 9 ], a22 = _values[ 10 ], a23 = _values[ 11 ],
        a30 = _values[ 12 ], a31 = _values[ 13 ], a32 = _values[ 14 ], a33 = _values[ 15 ];

      float b00 = a00 * a11 - a01 * a10;
      float b01 = a00 * a12 - a02 * a10;
      float b02 = a00 * a13 - a03 * a10;
      float b03 = a01 * a12 - a02 * a11;
      float b04 = a01 * a13 - a03 * a11;
      float b05 = a02 * a13 - a03 * a12;
      float b06 = a20 * a31 - a21 * a30;
      float b07 = a20 * a32 - a22 * a30;
      float b08 = a20 * a33 - a23 * a30;
      float b09 = a21 * a32 - a22 * a31;
      float b10 = a21 * a33 - a23 * a31;
      float b11 = a22 * a33 - a23 * a32;

      float det = b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06;

      float invDet = 1.0f / det;

      result._values[ 0 ] = ( a11 * b11 - a12 * b10 + a13 * b09 ) * invDet;
      result._values[ 1 ] = ( a02 * b10 - a01 * b11 - a03 * b09 ) * invDet;
      result._values[ 2 ] = ( a31 * b05 - a32 * b04 + a33 * b03 ) * invDet;
      result._values[ 3 ] = ( a22 * b04 - a21 * b05 - a23 * b03 ) * invDet;
      result._values[ 4 ] = ( a12 * b08 - a10 * b11 - a13 * b07 ) * invDet;
      result._values[ 5 ] = ( a00 * b11 - a02 * b08 + a03 * b07 ) * invDet;
      result._values[ 6 ] = ( a32 * b02 - a30 * b05 - a33 * b01 ) * invDet;
      result._values[ 7 ] = ( a20 * b05 - a22 * b02 + a23 * b01 ) * invDet;
      result._values[ 8 ] = ( a10 * b10 - a11 * b08 + a13 * b06 ) * invDet;
      result._values[ 9 ] = ( a01 * b08 - a00 * b10 - a03 * b06 ) * invDet;
      result._values[ 10 ] = ( a30 * b04 - a31 * b02 + a33 * b00 ) * invDet;
      result._values[ 11 ] = ( a21 * b02 - a20 * b04 - a23 * b00 ) * invDet;
      result._values[ 12 ] = ( a11 * b07 - a10 * b09 - a12 * b06 ) * invDet;
      result._values[ 13 ] = ( a00 * b09 - a01 * b07 + a02 * b06 ) * invDet;
      result._values[ 14 ] = ( a31 * b01 - a30 * b03 - a32 * b00 ) * invDet;
      result._values[ 15 ] = ( a20 * b03 - a21 * b01 + a22 * b00 ) * invDet;

      return result;
    }

    friend Matrix4 operator*( const Matrix4& a, const Matrix4& b )
    {
      /*std::array<float, 16> ae = a._values;
      std::array<float, 16> be = b._values;
      std::array<float, 16> te;

      float a11 = ae[ 0 ], a12 = ae[ 4 ], a13 = ae[ 8 ], a14 = ae[ 12 ];
      float a21 = ae[ 1 ], a22 = ae[ 5 ], a23 = ae[ 9 ], a24 = ae[ 13 ];
      float a31 = ae[ 2 ], a32 = ae[ 6 ], a33 = ae[ 10 ], a34 = ae[ 14 ];
      float a41 = ae[ 3 ], a42 = ae[ 7 ], a43 = ae[ 11 ], a44 = ae[ 15 ];

      float b11 = be[ 0 ], b12 = be[ 4 ], b13 = be[ 8 ], b14 = be[ 12 ];
      float b21 = be[ 1 ], b22 = be[ 5 ], b23 = be[ 9 ], b24 = be[ 13 ];
      float b31 = be[ 2 ], b32 = be[ 6 ], b33 = be[ 10 ], b34 = be[ 14 ];
      float b41 = be[ 3 ], b42 = be[ 7 ], b43 = be[ 11 ], b44 = be[ 15 ];

      te[ 0 ] = a11 * b11 + a12 * b21 + a13 * b31 + a14 * b41;
      te[ 4 ] = a11 * b12 + a12 * b22 + a13 * b32 + a14 * b42;
      te[ 8 ] = a11 * b13 + a12 * b23 + a13 * b33 + a14 * b43;
      te[ 12 ] = a11 * b14 + a12 * b24 + a13 * b34 + a14 * b44;

      te[ 1 ] = a21 * b11 + a22 * b21 + a23 * b31 + a24 * b41;
      te[ 5 ] = a21 * b12 + a22 * b22 + a23 * b32 + a24 * b42;
      te[ 9 ] = a21 * b13 + a22 * b23 + a23 * b33 + a24 * b43;
      te[ 13 ] = a21 * b14 + a22 * b24 + a23 * b34 + a24 * b44;

      te[ 2 ] = a31 * b11 + a32 * b21 + a33 * b31 + a34 * b41;
      te[ 6 ] = a31 * b12 + a32 * b22 + a33 * b32 + a34 * b42;
      te[ 10 ] = a31 * b13 + a32 * b23 + a33 * b33 + a34 * b43;
      te[ 14 ] = a31 * b14 + a32 * b24 + a33 * b34 + a34 * b44;

      te[ 3 ] = a41 * b11 + a42 * b21 + a43 * b31 + a44 * b41;
      te[ 7 ] = a41 * b12 + a42 * b22 + a43 * b32 + a44 * b42;
      te[ 11 ] = a41 * b13 + a42 * b23 + a43 * b33 + a44 * b43;
      te[ 15 ] = a41 * b14 + a42 * b24 + a43 * b34 + a44 * b44;

      return Matrix4( te );*/
      Matrix4 result;
      /*std::copy( std::begin( result._values ), std::end( result._values ), 
        std::begin( _values ) );*/

      for ( unsigned int i = 0; i < 4; ++i )
      {
        for ( unsigned int j = 0; j < 4; ++j )
        {
          for ( unsigned int k = 0; k < 4; ++k )
          {
            result[ i * 4 + j ] += a[ i * 4 + k ] * b[ k * 4 + j ];
          }
        }
      }

      return result;
    }
    friend Matrix4& operator*=( Matrix4& u, const Matrix4& v )
    {
      u = u * v;
      return u;
    }

    friend Vector4 operator*( const Matrix4& m, const Vector4& v )
    {
      Vector4 result;
      result[ 0 ] = 
        m[ 0 ] * v[ 0 ] +
        m[ 1 ] * v[ 1 ] +
        m[ 2 ] * v[ 2 ] +
        m[ 3 ] * v[ 3 ];
      result[ 1 ] = 
        m[ 4 ] * v[ 0 ] +
        m[ 5 ] * v[ 1 ] +
        m[ 6 ] * v[ 2 ] +
        m[ 7 ] * v[ 3 ];
      result[ 2 ] = 
        m[ 8 ] * v[ 0 ] +
        m[ 9 ] * v[ 1 ] +
        m[ 10 ] * v[ 2 ] +
        m[ 11 ] * v[ 3 ];
      result[ 3 ] = 
        m[ 12 ] * v[ 0 ] +
        m[ 13 ] * v[ 1 ] +
        m[ 14 ] * v[ 2 ] +
        m[ 15 ] * v[ 3 ];

      return result;
    }

    bool operator==( const Matrix4& v ) const
    {
      return std::equal( _values.begin( ), _values.end( ), v._values.begin( ) );
    }

    bool operator!=( const Matrix4& v ) const
    {
      return !( *this == v );
    }
   public:
    std::array<float, 16> _values;
  };

}//NS


#endif // WRAPPER_H
