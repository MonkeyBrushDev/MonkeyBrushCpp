#ifndef __MB_COMPUTE_BATCHQUEUE__
#define __MB_COMPUTE_BATCHQUEUE__

#include "Visitor.hpp"
#include "../Rendering/BatchQueue.hpp"
#include <mb/api.h>

namespace mb
{
  class Group;
  class Geometry;
  class Light;

  class ComputeBatchQueue :
    public Visitor
  {
  public:
    MB_API
    ComputeBatchQueue( Camera* cam, BatchQueue *rq );
    MB_API
    virtual ~ComputeBatchQueue( );
    MB_API
    virtual void traverse( Node* n ) override;
    MB_API
    virtual void visitGroup( Group* g ) override;
    MB_API
    virtual void visitGeometry( Geometry* n ) override;
    MB_API
    virtual void visitLight( Light* l ) override;
  protected:
    Camera* camera;
    BatchQueue* rq;
  };
}

/* TODO
if ( camera->layer( ).check( geometry->layer( ) ) )
{
rq->pushGeometry( geometry );
}
*/

#endif /* __MB_COMPUTE_BATCHQUEUE__ */
