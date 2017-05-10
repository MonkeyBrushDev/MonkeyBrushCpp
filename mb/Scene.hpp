#ifndef __MB_SCENE__
#define __MB_SCENE__

#include "scenegraph/Group.hpp"

#include <mb/api.h>

namespace mb
{
  class Scene
    : public Group
  {
  public:
    MB_API
    Scene( const std::string& name )
      : Group( name )
    {
    }
  };
}

#endif /* __MB_SCENE__ */
