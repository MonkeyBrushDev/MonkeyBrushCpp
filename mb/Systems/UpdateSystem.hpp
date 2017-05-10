#ifndef __MB_UPDATE_SYSTEM__
#define __MB_UPDATE_SYSTEM__

#include "System.hpp"

namespace mb
{
  class UpdateSystem: public System
  {
  public:
    UpdateSystem( void );
    virtual bool start( void ) override;
    virtual void stop( void ) override;

  protected:
    virtual void update( void );
  };
}

#endif /* __MB_UPDATE_SYSTEM__ */
