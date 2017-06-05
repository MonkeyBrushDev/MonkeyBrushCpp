#ifndef __MB_FREE_CAMERA_COMPONENT__
#define __MB_FREE_CAMERA_COMPONENT__

#include <mb/api.h>
#include "Component.hpp"
#include "../Maths/Vector3.hpp"
#include "../Maths/Quaternion.hpp"

namespace mb
{
  class FreeCameraComponent: public Component
  {
    IMPLEMENT_COMPONENT( FreeCameraComponent )
  public:
    MB_API
    virtual void start( void ) override;
    MB_API
    virtual void update( const mb::Clock& clock ) override;
  public:
    float fastMovementSpeed = 5.0f;
  protected:
    mb::Vector3 initPosition;
    mb::Quaternion initRotation;
  };
}

#endif /* __MB_FREE_CAMERA_COMPONENT__ */
