/**
 * Copyright (c) 2017, Monkey Brush
 * All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

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
