#ifndef __MB_SEPIA_EFFECT__
#define __MB_SEPIA_EFFECT__

#include "ImageEffect.hpp"

namespace mb
{
  class Camera;

  class SepiaToneEffect :
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

#endif /* __MB_SEPIA_EFFECT__ */
