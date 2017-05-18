#ifndef __MB_PARAMETRIC_PRIMITIVE__
#define __MB_PARAMETRIC_PRIMITIVE__

#include "Primitive.hpp"

namespace mb
{
  class ParametricPrimitive: public Primitive
  {
  public:
    ParametricPrimitive( Primitive::Type type )
    : Primitive( type )
    {

    }
  };
}

#endif /* __MB_PARAMETRIC_PRIMITIVE__ */
