#ifndef __MB_PRIMITIVE__
#define __MB_PRIMITIVE__

#include <string>
#include <iostream>
#include <mb/api.h>

namespace mb
{
  class Primitive
  {
  public:
    enum Type
    {
      POINTS,
      LINES,
      LINE_LOOP,
      LINE_STRIP,
      TRIANGLES,
      TRIANGLE_FAN,
      TRIANGLE_STRIP
    };
    /*explicit Primitive( Primitive::Type type = Primitive::Type::TRIANGLES )
    {

    }*/
    MB_API
    Primitive::Type type( void ) const
    {
      return _type;
    }

    /*void setVertexBuffer( VBO* vbo )
    {
      _vertexBuffer = vbo;
    }*/

    MB_API
    Primitive( const std::string& name_ )
      : name( name_ )
    {
      _type = Type::TRIANGLES;
    }
    MB_API
    void render( )
    {
      std::cout << "\t-Primitive '" << name << "'" << std::endl;
    }
    Type _type;
    std::string name;
  };
}

#endif /* __MB_PRIMITIVE__ */
