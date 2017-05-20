#ifndef __MB_IMAGE_EFFECT__
#define __MB_IMAGE_EFFECT__

#include <mb/api.h>
#include <memory>

namespace mb
{
  class Camera;
  class Renderer;
  class ImageEffect
  {
  public:
    MB_API
    // TODO Renderer?
    virtual void apply( Renderer* r, Camera* camera ) = 0;
    MB_API
    // TODO Renderer?
    virtual void compute( Renderer* r, Camera* camera ) = 0;

    bool enabled = true;
  protected:

  };
  typedef std::shared_ptr< ImageEffect > ImageEffectPtr;
}

#endif /* __MB_IMAGE_EFFECT__ */
