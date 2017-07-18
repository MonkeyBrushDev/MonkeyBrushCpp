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

    MB_API
    mb::Renderer* getRenderer( void ) const
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
