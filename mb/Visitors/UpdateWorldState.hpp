#ifndef __MB_UPDATE_WORLD_STATE__
#define __MB_UPDATE_WORLD_STATE__

#include "Visitor.hpp"
#include <mb/api.h>

namespace mb
{
  class UpdateWorldState :
    public Visitor
  {
  public:
    MB_API
    UpdateWorldState( );
    MB_API
    virtual ~UpdateWorldState( );
    MB_API
    virtual void visitNode( Node *node ) override;
    MB_API
    virtual void visitGroup( Group *node ) override;
  };
}

#endif /* __MB_UPDATE_WORLD_STATE__ */
