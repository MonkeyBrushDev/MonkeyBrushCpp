#ifndef __MB_RENDERER__
#define __MB_RENDERER__

#include "../Scenegraph/Camera.hpp"
#include "../Scenegraph/Geometry.hpp"

#include "../Maths/Rect.hpp"

#include <vector>
#include "Material.hpp"
#include "BatchQueue.hpp"

namespace mb
{
  class RenderingPass;

  class Renderer
  {
  public:
    Renderer( );

    virtual ~Renderer( );
    virtual void setViewport( const Viewport& ) { }

    virtual void beginRender( void );
    virtual void clearBuffers( void ) = 0;
    virtual void render( BatchQueuePtr bq, RenderingPass* rp );
    virtual void endRender( void );
    virtual void configure( void ) { }
  public:
    virtual void bindFBO( unsigned int ) { }
    virtual void unbindFBO( unsigned int ) { }
    virtual void bindProgram( unsigned int ) { }
    virtual void unbindProgram( unsigned int ) { }
    virtual void drawPrimitive( MaterialPtr, Primitive* ) { }

    // virtual void drawBuffer( Material* material ... ) { }
  };
}

#endif /* __MB_RENDERER__ */
