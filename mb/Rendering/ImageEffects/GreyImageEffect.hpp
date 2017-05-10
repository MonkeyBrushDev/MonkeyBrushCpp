#ifndef __MB_GREY_IMAGE_EFFECT__
#define __MB_GREY_IMAGE_EFFECT__

#include "ImageEffect.hpp"

namespace mb
{
  class Camera;

  class GreyToneEffect :
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

#endif /* __MB_GREY_IMAGE_EFFECT__ */
