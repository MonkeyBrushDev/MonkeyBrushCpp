#ifndef __MB_CHILDREN_COUNTER_VISITOR__
#define __MB_CHILDREN_COUNTER_VISITOR__

#include "Visitor.hpp"
#include <mb/api.h>

namespace mb
{
  class ChildrenCounterVisitor :
    public Visitor
  {
  public:
    MB_API
    ChildrenCounterVisitor( );
    MB_API
    virtual ~ChildrenCounterVisitor( );
    MB_API
    virtual void reset( ) override;
    MB_API
    virtual void traverse( Node* n ) override;
    MB_API
    virtual void visitNode( Node* n ) override;
    MB_API
    virtual void visitGroup( Group* g ) override;

  //protected:
    unsigned int _childrens;
  };
}

#endif /* __MB_CHILDREN_COUNTER_VISITOR__ */
