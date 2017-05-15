#ifndef __MB_RAY__
#define __MB_RAY__

#include <mb/api.h>

#include "../Boundings/BoundingVolume.hpp"

// TODO: Migrate to original Ray in old MonkeyBrush

namespace mb
{
  class Ray
  {
  public:
    Ray( )
    {
    }
    Ray( float xx, float yy, float zz )
    {
      this->x = xx;
      this->y = yy;
      this->z = zz;
    }
    float x;
    float y;
    float z;

    bool intersect( const BoundingVolume* bv )
    {
      return true;
    }
  };
}

#endif /* __MB_RAY__ */
