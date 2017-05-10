#ifndef __MB_PRINT_NAME_VISITOR__
#define __MB_PRINT_NAME_VISITOR__

#include "LambdaVisitor.hpp"
#include <mb/api.h>

namespace mb
{
  class PrintNameVisitor :
    public LambdaVisitor
  {
  public:
    MB_API
    PrintNameVisitor( );
    MB_API
    virtual ~PrintNameVisitor( );
  };
}

#endif /* __MB_PRINT_NAME_VISITOR__ */
