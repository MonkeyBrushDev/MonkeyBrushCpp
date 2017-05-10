#ifndef __MB_RENDER_SYSTEM__
#define __MB_RENDER_SYSTEM__

#include "System.hpp"

namespace mb
{
  class RenderSystem: public System
  {
  public:
    RenderSystem( void );
    virtual bool start( void ) override;
    virtual void stop( void ) override;
  };
}

#endif /* __MB_RENDER_SYSTEM__ */
