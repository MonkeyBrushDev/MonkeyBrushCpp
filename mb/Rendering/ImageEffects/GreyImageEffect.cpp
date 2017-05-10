#include "GreyImageEffect.hpp"
#include "../../Scenegraph/Camera.hpp"
#include "../Renderer.hpp"

namespace mb
{
  void GreyToneEffect::compute( Renderer*, Camera* )
  {

  }

  void GreyToneEffect::apply( Renderer*, Camera* camera )
  {
    // bind shader, texture, draw and unbind texture and shader
    //std::cout << "Aplicando GreyToneEffect" << std::endl;
    std::cout << "Bind program (GreyToneEffect)" << std::endl;
    std::cout << "\tBind texture" << std::endl;
    std::cout << "\tDraw ScreenQuad" << std::endl;
    std::cout << "\tUnbind texture" << std::endl;
    std::cout << "Unbind program (GreyToneEffect)" << std::endl;
  }
}
