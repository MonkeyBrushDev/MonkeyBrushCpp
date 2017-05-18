#include "Renderer.hpp"
#include "RenderPasses/RenderingPass.hpp"
#include "BatchQueue.hpp"
#include "../Scenegraph/Camera.hpp"

namespace mb
{
  Renderer::Renderer( )
  {
  }

  Renderer::~Renderer( )
  {
  }

  void Renderer::beginRender( void )
  {
    std::cout << "Set viewport" << std::endl;
  }

  void Renderer::render( BatchQueuePtr bq, RenderingPass* rp )
  {
    rp->render( this, bq, bq->camera( ) );
  }

  void Renderer::endRender( void )
  {
    // Clear data
    std::cout << "unbind renderer" << std::endl;
  }
}
