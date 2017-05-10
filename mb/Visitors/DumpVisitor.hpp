#ifndef __MB_DUMP_VISITOR__
#define __MB_DUMP_VISITOR__

#include "Visitor.hpp"
#include <string>

#include <mb/api.h>

namespace mb
{
  class DumpVisitor :
    public Visitor
  {
  public:
    MB_API
    DumpVisitor( );
    MB_API
    virtual ~DumpVisitor( );

    MB_API
    virtual void traverse( Node *node ) override;

    MB_API
    virtual void visitNode( Node *node ) override;
    MB_API
    virtual void visitGroup( Group *group ) override;
    MB_API
    virtual void visitGeometry( Geometry *geometry ) override;
    MB_API
    virtual void visitCamera( Camera *camera ) override;
    MB_API
    virtual void visitLight( Light *light ) override;
  private:
    void _dumpNode( Node *node, const std::string& type );
    int _auxLevel = 0;
  };
}

#endif /* __NODESDUMP_VISITOR__ */
