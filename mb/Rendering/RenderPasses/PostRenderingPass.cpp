#include "PostRenderingPass.hpp"
#include "StandardRenderingPass.hpp"
#include "../BatchQueue.hpp"
#include "../Renderer.hpp"

namespace mb
{
  int PostRenderingPass::FBOCOUNTER = 0;

  PostRenderingPass::PostRenderingPass( RenderingPass* sceneRP )
  : _sceneRenderingPass ( sceneRP )
  {
    _fbo = ++PostRenderingPass::FBOCOUNTER;
  }

  void PostRenderingPass::render( Renderer* renderer, BatchQueuePtr bq, Camera* cam )
  {
    renderer->bindFBO( _fbo );
    _sceneRenderingPass->render( renderer, bq, cam );
    renderer->unbindFBO( _fbo );

    applyImageEffects( renderer, cam );
  }
}
