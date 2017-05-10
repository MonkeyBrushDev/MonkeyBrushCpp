#include "BatchQueue.hpp"

namespace mb
{
  BatchQueue::BatchQueue( )
  {
    _renderables[ RenderableType::OPAQUE ] = std::vector<Renderable*>( );
    _renderables[ RenderableType::TRANSPARENT ] = std::vector<Renderable*>( );
  }

  BatchQueue::~BatchQueue( )
  {
    reset( );
  }

  void BatchQueue::reset( )
  {
    setCamera( nullptr );
    _lights.clear( );
    for ( auto &it : _renderables )
    {
      it.second.clear( );
    }
    _renderables.clear( );
  }
  void BatchQueue::setCamera( Camera* c )
  {
    _camera = c;
  }
  Camera* BatchQueue::camera( )
  {
    return _camera;
  }
  std::vector<Renderable*> BatchQueue::renderables( RenderableType t )
  {
    return _renderables[ t ];
  }
  void BatchQueue::pushGeometry( Geometry* g )
  {
    auto mr = g->getComponent< MeshRenderer >( );
    if ( mr == nullptr )
    {
      return;
    }

    Renderable* r = new Renderable( );
    r->material = 1;
    r->geom = g;

    _renderables[ RenderableType::OPAQUE ].push_back( r );
  }
  void BatchQueue::pushLight( Light * l )
  {
    _lights.push_back( l );
  }
}
