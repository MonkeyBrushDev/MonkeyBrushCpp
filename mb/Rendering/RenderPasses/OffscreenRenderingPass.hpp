#ifndef __MB_OFFSCREEN_RP__
#define __MB_OFFSCREEN_RP__

#include "RenderingPass.hpp"

namespace mb
{
  struct Renderable;

  class OffscreenRenderingPass: public RenderingPass
  {
  public:
    MB_API
    OffscreenRenderingPass( unsigned int fbo );
    MB_API
    OffscreenRenderingPass( unsigned int fbo, RenderingPass* sceneRenderingPass );
    MB_API
    void render( Renderer* renderer, BatchQueue* rq, Camera* c );
    MB_API
    unsigned int targetFBO( void )
    {
      return _fbo;
    }
    MB_API
    RenderingPass* sceneRenderingPass( void )
    {
      return _sceneRenderingPass;
    }
  protected:
    unsigned int _fbo;
    RenderingPass* _sceneRenderingPass;
  };
}

#endif /* __MB_OFFSCREEN_RP__ */
