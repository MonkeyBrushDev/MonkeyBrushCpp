#ifndef __MB_STANDARD_RP__
#define __MB_STANDARD_RP__

#include "RenderingPass.hpp"

#include "../Renderer.hpp"
#include "../BatchQueue.hpp"

namespace mb
{
  class StandardRenderingPass: public RenderingPass
  {
  public:
    MB_API
    void render( Renderer* renderer, BatchQueuePtr bq, Camera* c );
  protected:
    void renderOpaqueObjects( Renderer* renderer, BatchQueuePtr bq, Camera* c );
    void renderTransparentObjects( Renderer* renderer, BatchQueuePtr bq, Camera* c );
    void renderStandardGeometry( Renderer* renderer, Renderable* renderable );
  };
}

#endif /* __MB_STANDARD_RP__ */
