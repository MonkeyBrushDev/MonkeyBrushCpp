#include "OffscreenRenderingPass.hpp"
#include "StandardRenderingPass.hpp"
#include "../BatchQueue.hpp"

namespace mb
{
  OffscreenRenderingPass::OffscreenRenderingPass( unsigned int fbo )
    : OffscreenRenderingPass( fbo, new StandardRenderingPass( ) )
  {
  }

  OffscreenRenderingPass::OffscreenRenderingPass( unsigned int fbo, RenderingPass* sceneRenderingPass )
  : _fbo( fbo )
  , _sceneRenderingPass( sceneRenderingPass )
  {
  }

  void OffscreenRenderingPass::render( Renderer* renderer, BatchQueue* rq, Camera* cam )
  {
    std::cout << "Bind FBO" << std::endl;
    //renderer->bindFBO( targetFBO );
    _sceneRenderingPass->render( renderer, rq, cam );
    //renderer->unbindFBO( );
    std::cout << "Unbind FBO" << std::endl;
    applyImageEffects( renderer, cam );
  }
}
