#ifndef __MB_FETCH_GEOMETRY__
#define __MB_FETCH_GEOMETRY__

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
    ComputeBatchQueue( Camera* cam, BatchQueuePtr bq );
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
    BatchQueuePtr bq;
  };
}

/* TODO
if ( camera->layer( ).check( geometry->layer( ) ) )
{
rq->pushGeometry( geometry );
}
*/

#endif /* __MB_FETCH_GEOMETRY__ */
