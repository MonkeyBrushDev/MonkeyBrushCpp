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

#ifndef __MB_OFFSCREEN_RP__
#define __MB_OFFSCREEN_RP__

#include "RenderingPass.hpp"

namespace mb
{
  struct Renderable;

  class OffscreenRenderingPass: public RenderingPass
  {
  public:
    MB_API
    OffscreenRenderingPass( unsigned int fbo );
    MB_API
    OffscreenRenderingPass( unsigned int fbo, RenderingPass* sceneRenderingPass );
    MB_API
    void render( Renderer* renderer, BatchQueuePtr bq, Camera* c );
    MB_API
    unsigned int targetFBO( void )
    {
      return _fbo;
    }
    MB_API
    RenderingPass* sceneRenderingPass( void )
    {
      return _sceneRenderingPass;
    }
  protected:
    unsigned int _fbo;
    RenderingPass* _sceneRenderingPass;
  };
}

#endif /* __MB_OFFSCREEN_RP__ */
