#include "Light.hpp"

namespace mb
{
  Light::Light( )
  : Node( std::string("Light") )
  , shadowType( ShadowType::NO_SHADOW )
  {
  }

  Light::~Light( )
  {
  }

  void Light::accept( Visitor& visitor )
  {
    visitor.visitLight( this );
  }
}
