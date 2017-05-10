#ifndef __MB_CUSTOM_COMPONENT__
#define __MB_CUSTOM_COMPONENT__

#include "Component.hpp"
#include <mb/api.h>

namespace mb
{
  class CustomComponent : public Component
  {
    IMPLEMENT_COMPONENT( CustomComponent )
  public:
    MB_API
    CustomComponent( );
    MB_API
    virtual ~CustomComponent( );
    int v;
  };
}

#endif /* __MB_CUSTOM_COMPONENT__ */
