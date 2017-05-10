#include "RenderingPass.hpp"

#include "../Renderer.hpp"
#include "../BatchQueue.hpp"
#include "../ImageEffects/ImageEffect.hpp"
#include "../../Scenegraph/Camera.hpp"

/*void RenderingPass::render( Renderer* renderer, BatchQueue* rq, Camera* c )
{

}*/

namespace mb
{
  void RenderingPass::applyImageEffects( Renderer *renderer, Camera *camera )
  {
    for ( auto& ie : _imageEffects )
    {
      unsigned int fbo = 0;
      ie->compute( renderer, camera );

      renderer->bindFBO( fbo );
      ie->apply( renderer, camera );
      renderer->unbindFBO( fbo );
      // Swap FBO?
      swapBuffers( renderer );
    }
  }

  void RenderingPass::swapBuffers( Renderer* r )
  {
    //auto source = 1;
    //auto destination = 2;

    std::cout << "Set source buffer with destination texture" << std::endl;
    //renderer->setFBO(SOURCE, destination);
    std::cout << "Set destination buffer with source texture" << std::endl;
    //renderer->setFBO(DESTINATION, source);
  }
}
