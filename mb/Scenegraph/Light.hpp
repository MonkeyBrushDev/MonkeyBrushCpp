#ifndef __MB_LIGHT__
#define __MB_LIGHT__

#include "Node.hpp"
#include <mb/api.h>

namespace mb
{
  class Light :
    public Node
  {
    enum class ShadowType
    {
      NO_SHADOW,
      SOFT_SHADOW,
      HARD_SHADOW
    };
  public:
    MB_API
    Light( void );
    MB_API
    ~Light( void );

  public:
    MB_API
    virtual void accept( Visitor& v ) override;

  public:
    // TODO: Color4 color;
    ShadowType shadowType;
    float strength = 1.0f;
    float bias = 0.05f;
    float normalBias = 0.4f;
    float nearPlane = 0.2f;
  };
}

#endif /* __MB_LIGHT__ */
