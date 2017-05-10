#ifndef __MB_START_COMPONENTS__
#define __MB_START_COMPONENTS__

#include "LambdaVisitor.hpp"
#include <mb/api.h>

namespace mb
{
  class StartComponents :
    public LambdaVisitor
  {
  public:
    MB_API
    StartComponents( );
    MB_API
    virtual ~StartComponents( );
  };
}

#endif /* __MB_START_COMPONENTS__ */
