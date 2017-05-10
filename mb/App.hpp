#ifndef __MB_APP__
#define __MB_APP__

#include <mb/api.h>
#include "Scene.hpp"
#include "Scenegraph/Camera.hpp"
#include "Maths/Clock.hpp"

#include <unordered_map>

#include "Systems/System.hpp"

#include "Rendering/Renderer.hpp"

namespace mb
{
  class App
  {
  public:
    MB_API
    App( void );
    MB_API
    virtual ~App( void );
    MB_API
    void setSceneNode( Scene* node );
    MB_API
    virtual int run( void );

    virtual void start( void );
    virtual bool update( void );
    virtual void stop( void );

    System* system( const std::string& name )
    {
      return _systems[ name ];
    }
  protected:
    void startSystems( void )
    {
      std::cout << "Starting systems" << std::endl;
      for ( auto& sys : _systems )
      {
        if ( sys.second != nullptr )
        {
          sys.second->start( );
        }
      }
    }
    void stopSystems( void )
    {
      std::cout << "Stopping systems" << std::endl;
      for ( auto& sys : _systems )
      {
        if ( sys.second != nullptr )
        {
          sys.second->stop( );
        }
      }
    }
    void addSystem( System* sys )
    {
      // TODO: Check if exist
      _systems[ sys->name( ) ] = sys;
    }
    void forEachCamera( std::function< void( Camera * ) > callback )
    {
      for ( auto camera : _cameras )
      {
        callback( camera );
      }
    }
  protected:
    Clock _simulationClock;
    Scene* _scene;
    Renderer *_renderer;
    std::vector<Camera*> _cameras;

    std::unordered_map< std::string, System*> _systems;
  };
}

#endif /* __MB_APP__ */
