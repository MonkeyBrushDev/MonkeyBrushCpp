#ifndef WRAPPER_H
#define WRAPPER_H

#include <mb/api.h>
#include "Vect3.hpp"
#include "../Scenegraph/Node.hpp"

#include <vector>
#include <iostream>

namespace mb
{

 class Mat4
 {

  public:

    MB_API
    Mat4( void );

    MB_API
    Mat4( const std::array<float, 16> values );

    MB_API
    void copy( const Mat4& m );

    MB_API
    std::array<float, 16> values( void ){ return _values; }

    MB_API
    void compose( Vect3& position, Quaternion& quaternion, Vect3& scale );

    MB_API
    static Mat4 perspective( const float& fovy, const float& aspect,
                             const float& near, const float& far );

    MB_API
    static Mat4 orthographic( const float& left, const float& right,
                              const float& bottom, const float& top,
                              const float& near, const float& far );

    static Mat4 mult( const Mat4& a, const Mat4& b );

   public:

    std::array<float, 16> _values;

  };

}//NS


#endif // WRAPPER_H
