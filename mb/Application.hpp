#ifndef __MB_APPLICATION__
#define __MB_APPLICATION__

#include <mb/api.h>
#include "Scenegraph/Group.hpp"
#include "Scenegraph/Camera.hpp"
#include "Maths/Clock.hpp"

#include <unordered_map>

namespace mb
{
  class Application
  {
  public:
    MB_API
    Application( void );
    MB_API
    virtual ~Application( void );
    MB_API
    void setSceneNode( Scene* node );
    MB_API
    virtual int run( void );
    MB_API
    virtual bool update( void );
  protected:
    Clock _simulationClock;
    Group/*Scene*/* _scene;
    //Renderer *_renderer;
    std::vector<Camera*> _cameras;
  };
}

#endif /* __MB_APPLICATION__ */
