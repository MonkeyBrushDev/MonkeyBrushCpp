#ifndef __MB_SPHERICAL__
#define __MB_SPHERICAL__

#include <mb/api.h>

#include "Vector3.hpp"

namespace mb
{
  class Spherical
  {
  public:
    MB_API
    mb::Vector3 toCartesian( void );
    MB_API
    static Spherical cartesianToSpherical( mb::Vector3 cartCoords );
    MB_API
    static mb::Vector3 sphericalToCartesian( float r, float p, float e );
  protected:
    float _radius;
    float _polar;
    float _elevation;
  };
}

#endif /* __MB_SPHERICAL__ */
