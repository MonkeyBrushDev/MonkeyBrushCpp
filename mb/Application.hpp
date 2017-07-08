#ifndef __MB_APPLICATION__
#define __MB_APPLICATION__

#include <mb/api.h>
#include "Scenegraph/Group.hpp"
#include "Scenegraph/Camera.hpp"
#include "Rendering/Renderer.hpp"
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
    void setSceneNode( Group* node );
    MB_API
    virtual int run( void );
    MB_API
    virtual bool update( void );

    const Renderer* getRenderer( void )
    {
      return _renderer;
    }
    Renderer* renderer( void )
    {
      return _renderer;
    }

    bool debug = false;
  protected:
    Clock _simulationClock;
    Group* _scene; // Scene*
    Renderer* _renderer;
    std::vector<Camera*> _cameras;
  };
}

#endif /* __MB_APPLICATION__ */
