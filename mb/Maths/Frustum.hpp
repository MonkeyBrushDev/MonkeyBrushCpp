#ifndef __MB_FRUSTUM__
#define __MB_FRUSTUM__

#include <math.h>
#include <array>
#include <mb/api.h>

namespace mb
{
  class Frustum
  {
    enum {
      FRUSTUM_R_MIN = 0,
      FRUSTUM_R_MAX = 1,
      FRUSTUM_U_MIN = 2,
      FRUSTUM_U_MAX = 3,
      FRUSTUM_D_MIN = 4,
      FRUSTUM_D_MAX = 5,
    };
  public:
    Frustum( void );
    MB_API
    Frustum( const float& fov/* = 45.0f*/, const float& ar/* = 1.0f*/,
      const float& near/* = 0.1f*/, const float& far/* = 1000.0f*/ );
  protected:
    std::array< float, 6 > _data;
  };
}

#endif /* __MB_FRUSTUM__ */
