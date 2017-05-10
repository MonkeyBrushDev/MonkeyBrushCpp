#include "SepiaImageEffect.hpp"
#include "../../Scenegraph/Camera.hpp"
#include "../Renderer.hpp"

namespace mb
{
  void SepiaToneEffect::compute( Renderer*, Camera* )
  {
  }

  void SepiaToneEffect::apply( Renderer*,  Camera* camera )
  {
    // bind shader, texture, draw and unbind texture and shader
    //std::cout << "Apply SepiaToneEffect" << std::endl;
    std::cout << "Bind program (SepiaToneEffect)" << std::endl;
    std::cout << "\tBind texture" << std::endl;
    std::cout << "\tDraw ScreenQuad" << std::endl;
    std::cout << "\tUnbind texture" << std::endl;
    std::cout << "Unbind program (SepiaToneEffect)" << std::endl;
  }
}
