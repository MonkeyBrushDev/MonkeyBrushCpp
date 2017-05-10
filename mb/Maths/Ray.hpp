#ifndef __MB_RAY__
#define __MB_RAY__

#include <mb/api.h>

namespace mb
{
  class Ray
  {
  public:
    Ray( float xx, float yy, float zz )
    {
      this->x = xx;
      this->y = yy;
      this->z = zz;
    }
    float x;
    float y;
    float z;
  };
}

#endif /* __MB_RAY__ */
