#ifndef __MB_MESH_RENDERER__
#define __MB_MESH_RENDERER__

#include "Component.hpp"
#include <mb/api.h>

namespace mb
{
  class MeshRenderer :
    public Component
  {
    IMPLEMENT_COMPONENT( MeshRenderer )
  public:
    MB_API
      MeshRenderer( int vao );
    MB_API
    virtual ~MeshRenderer( );
  public:
    int vao;
  };
}

#endif /* __MB_MESH_RENDERER__ */
