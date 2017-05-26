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

#ifndef __MB_RENDERER__
#define __MB_RENDERER__

#include "../Scenegraph/Camera.hpp"
#include "../Scenegraph/Geometry.hpp"

#include "../Maths/Rect.hpp"

#include <vector>
#include "Material.hpp"
#include "BatchQueue.hpp"

namespace mb
{
  class RenderingPass;

  class Renderer
  {
  public:
    Renderer( );

    virtual ~Renderer( );
    virtual void setViewport( const Viewport& ) { }

    virtual void beginRender( void );
    virtual void clearBuffers( void ) = 0;
    virtual void render( BatchQueuePtr bq, RenderingPass* rp );
    virtual void endRender( void );
    virtual void configure( void ) { }
  public:
    virtual void bindFBO( unsigned int ) { }
    virtual void unbindFBO( unsigned int ) { }
    virtual void bindProgram( unsigned int ) { }
    virtual void unbindProgram( unsigned int ) { }
    virtual void drawPrimitive( MaterialPtr, Primitive* ) { }

    // virtual void drawBuffer( Material* material ... ) { }
  };
}

#endif /* __MB_RENDERER__ */
