#include "ImageEffect.hpp"
#include "../Renderer.hpp"

namespace mb
{
  void ImageEffect::renderScreen( Renderer* r, MaterialPtr m )
  {
    m->use( );
    r->drawScreenQuad( );
    m->unuse( );
  }
}
