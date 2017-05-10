#ifndef __MB_BLUR_IMAGE_EFFECT__
#define __MB_BLUR_IMAGE_EFFECT__

#include "ImageEffect.hpp"

namespace mb
{
  class Camera;

  class BlurToneEffect :
    public ImageEffect
  {
  public:
    MB_API
    virtual void compute( Renderer*, Camera* camera ) override;
    MB_API
    virtual void apply( Renderer*, Camera* camera ) override;
  protected:
    int shader;
  };
}

#include "BlurToneEffect.hpp"
#include "../../Scenegraph/Camera.hpp"
#include "Renderer.hpp"

namespace mb
{
  void compute( Renderer* r, Camera* c)
  {

  }
  void apply( Renderer* r, Camera* c)
  {

  }
}

#endif /* __MB_BLUR_IMAGE_EFFECT__ */
