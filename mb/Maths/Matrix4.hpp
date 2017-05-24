#ifndef WRAPPER_H
#define WRAPPER_H

#include <mb/api.h>
#include "Vector3.hpp"
#include "Quaternion.hpp"

#include <vector>
#include <iostream>

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
    std::array<float, 16> values( void ){ return _values; }

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
