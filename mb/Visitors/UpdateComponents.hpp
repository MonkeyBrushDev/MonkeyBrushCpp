#ifndef __MB_UPDATE_COMPONENTS__
#define __MB_UPDATE_COMPONENTS__

#include "LambdaVisitor.hpp"
#include <mb/api.h>

namespace mb
{
  class UpdateComponents :
    public LambdaVisitor
  {
  public:
    // TODO: USE CLOCK
    MB_API
    UpdateComponents( const float& dt );
    MB_API
    virtual ~UpdateComponents( );
  };
}

#endif /* __MB_UPDATE_COMPONENTS__ */
