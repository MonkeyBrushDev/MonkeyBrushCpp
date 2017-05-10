#ifndef __MB_RENDERING_PASS__
#define __MB_RENDERING_PASS__

#include <vector>
#include "../BatchQueue.hpp"
#include "../ImageEffects/ImageEffect.hpp"

namespace mb
{
  class Camera;
  class Renderer;

  class RenderingPass
  {
  public:
    //MB_API
    virtual void render( Renderer* renderer, BatchQueue* rq, Camera* c ) = 0;
    MB_API
    virtual void applyImageEffects( Renderer *renderer, Camera *camera );
    MB_API
    std::vector<ImageEffect*>& imageEffects( void )
    {
      return _imageEffects;
    }
  protected:
    std::vector< ImageEffect *> _imageEffects;

  private:
    void swapBuffers( Renderer* r );
  };
}

#endif /* __MB_RENDERING_PASS__ */
