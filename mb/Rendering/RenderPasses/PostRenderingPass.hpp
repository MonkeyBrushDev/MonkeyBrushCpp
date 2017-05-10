#ifndef __MB_MB_POST_RP__
#define __MB_MB_POST_RP__

#include "RenderingPass.hpp"

namespace mb
{
  struct Renderable;
  class Renderer;
  class BatchQueue;

  class PostRenderingPass: public RenderingPass
  {
  public:
    MB_API
    PostRenderingPass( RenderingPass* sceneRP );
    MB_API
    void render( Renderer* renderer, BatchQueue* rq, Camera* c );
  protected:
    RenderingPass *_sceneRenderingPass;

    int _fbo;

    // HARDCODED
    static int FBOCOUNTER;
  };
}

#endif /* __MB_POST_RP__ */
