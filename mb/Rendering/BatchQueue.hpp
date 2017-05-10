#ifndef __MB_BATCH_QUEUE__
#define __MB_BATCH_QUEUE__

#include <vector>
//#include <unordered_map>
#include <map>
#include "../Components/MeshRenderer.hpp"

#include "../Scenegraph/Light.hpp"
#include "../Scenegraph/Geometry.hpp"
#include "../Scenegraph/Camera.hpp"

#include <mb/api.h>

namespace mb
{
  struct Renderable
  {
    unsigned int material;
    Geometry* geom;
  };

  class BatchQueue
  {
  public:
    enum class RenderableType
    {
      OPAQUE,
      TRANSPARENT
    };
    MB_API
    BatchQueue( );
    MB_API
    virtual ~BatchQueue( );
    MB_API
    std::vector<Renderable*> renderables( RenderableType t );
    MB_API
    void pushGeometry( Geometry* g );
    MB_API
    void pushLight( Light * l );
    MB_API
    void reset( );
    MB_API
    void setCamera( Camera* c );
    MB_API
    Camera* camera( );
  protected:
    Camera* _camera;
    std::vector< Light* > _lights;
    // TODO std::unordered_map< RenderableType, std::vector< Renderable* >> _renderables;
    std::map< RenderableType, std::vector< Renderable* >> _renderables;
  };
}

#endif /* __MB_BATCH_QUEUE__ */
