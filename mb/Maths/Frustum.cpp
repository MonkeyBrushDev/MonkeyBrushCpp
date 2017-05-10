#include "Frustum.hpp"

namespace mb
{
  Frustum::Frustum( const float& fov, const float& ar,
    const float& near, const float& far )
  {
    _data[ FRUSTUM_U_MAX ] = near * std::tan( 0.5f * fov * 3.1415f / 180.0f );
    _data[ FRUSTUM_R_MAX ] = ar * _data[ FRUSTUM_U_MAX ];
    _data[ FRUSTUM_U_MIN ] = -_data[ FRUSTUM_U_MAX ];
    _data[ FRUSTUM_R_MIN ] = -_data[ FRUSTUM_R_MAX ];
    _data[ FRUSTUM_D_MIN ] = near;
    _data[ FRUSTUM_D_MAX ] = far;
  }
}
