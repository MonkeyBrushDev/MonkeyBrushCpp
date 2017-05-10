#ifndef __MB_ORBIT_CAMERA__
#define __MB_ORBIT_CAMERA__

#include "Component.hpp"
#include <mb/api.h>

namespace mb
{
  class OtherComponent : public Component
  {
    IMPLEMENT_COMPONENT( OtherComponent )
  public:
    MB_API
    OtherComponent( );
    MB_API
    virtual ~OtherComponent( );
  };
}

#endif /* __MB_ORBIT_CAMERA__ */
