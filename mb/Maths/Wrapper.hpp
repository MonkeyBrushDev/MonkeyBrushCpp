#ifndef WRAPPER_H
#define WRAPPER_H

#include <mb/api.h>
#include "Vect3.hpp"
#include "../Scenegraph/Node.hpp"

#include <vector>
#include <iostream>
#include <glm/glm.hpp>

namespace mb
{

 class Wrapper
 {

  public:

    MB_API
    Wrapper( void );

    MB_API
    Wrapper( const std::vector<float> values );

    MB_API
    void compose( Vect3& position, Quaternion& quaternion, Vect3& scale );

    MB_API
    static Wrapper perspective(const float& fovy, const float& aspect,
            const float& near, const float& far);

    MB_API
    static Wrapper orthographic( const float& left, const float& right,
                                 const float& bottom, const float& top,
                                 const float& near, const float& far );

   public:

    glm::vec3 _values;

  };

}//NS


#endif // WRAPPER_H
