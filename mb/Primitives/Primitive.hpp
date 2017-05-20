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
    enum class Type: short
    {
      POINTS = 0,
      LINES,
      LINE_LOOP,
      LINE_STRIP,
      TRIANGLES,
      TRIANGLE_FAN,
      TRIANGLE_STRIP
    };
    MB_API
    Primitive::Type type( void ) const;
    MB_API
    Primitive( Primitive::Type type = Primitive::Type::TRIANGLES );
    MB_API
    void render( void );
    Primitive::Type _type;
  };
}

#endif /* __MB_PRIMITIVE__ */
