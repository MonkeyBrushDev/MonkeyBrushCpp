#include "Frustum.hpp"
#include <cmath>

namespace mb
{
  Frustum::Frustum( const float& fov, const float& ar,
    const float& near, const float& far )
  {
    _data[ FRUSTUM_UMAX ] = near * std::tan( 0.5f * fov * 3.1415f / 180.0f );
    _data[ FRUSTUM_RMAX ] = ar * _data[ FRUSTUM_UMAX ];
    _data[ FRUSTUM_UMIN ] = -_data[ FRUSTUM_UMAX ];
    _data[ FRUSTUM_RMIN ] = -_data[ FRUSTUM_RMAX ];
    _data[ FRUSTUM_DMIN ] = near;
    _data[ FRUSTUM_DMAX ] = far;
  }
}
