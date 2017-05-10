#ifndef __MB_LAMBDA_VISITOR__
#define __MB_LAMBDA_VISITOR__

#include <functional>
#include "Visitor.hpp"
#include <mb/api.h>

namespace mb
{
  class LambdaVisitor :
    public Visitor
  {
  private:
    typedef std::function<void( Node* )> CallbackType;
  public:
    MB_API
      LambdaVisitor( CallbackType cb );
    MB_API
      virtual ~LambdaVisitor( );
    MB_API
      virtual void visitNode( Node* n ) override;
    MB_API
    virtual void visitGroup( Group* g ) override;
  private:
    CallbackType _callback;
  };
}

#endif /* __MB_LAMBDA_VISITOR__ */
