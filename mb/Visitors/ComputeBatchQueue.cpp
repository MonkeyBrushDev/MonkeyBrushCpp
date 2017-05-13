#include "ComputeBatchQueue.hpp"
#include "../Scenegraph/Camera.hpp"
#include "../Scenegraph/Group.hpp"
#include "../Scenegraph/Geometry.hpp"
#include "../Scenegraph/Light.hpp"

namespace mb
{
  ComputeBatchQueue::ComputeBatchQueue( Camera* c, BatchQueuePtr bq_ )
  : Visitor( )
  , camera( c )
  , bq( bq_ )
  {
  }

  ComputeBatchQueue::~ComputeBatchQueue( )
  {
  }

  void ComputeBatchQueue::visitGroup( Group *group )
  {
    // No ejecutamos culling de la cámara
    //  sobre los grupos porque los hijos pueden
    //  tener nodos útiles (?)
    Visitor::visitGroup( group );
  }

  void ComputeBatchQueue::traverse( Node* node )
  {
    bq->reset( );
    bq->setCamera( camera );
    // TODO: COMPUTE CULLING
    Visitor::traverse( node );
  }

  void ComputeBatchQueue::visitGeometry( Geometry *geometry )
  {
    // TODO: Culled camera layer and frustum culling

    if ( camera->layer( ).check( geometry->layer( ) ) )
    {
      bq->pushGeometry( geometry );
    }
    //bq->pushGeometry( geometry );
  }

  void ComputeBatchQueue::visitLight( Light *light )
  {
    bq->pushLight( light );
  }
}
