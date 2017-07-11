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

#ifndef __MB_OPENGL_RENDERER__
#define __MB_OPENGL_RENDERER__

#include "../Rendering/Renderer.hpp"

#include "../Scenegraph/Camera.hpp"
#include "../Scenegraph/Geometry.hpp"

#include "../Maths/Rect.hpp"

#include <vector>
#include "../Rendering/Material.hpp"
#include "../Rendering/BatchQueue.hpp"

#include <GL/glew.h>

namespace mb
{
  class OpenGLRenderer: public Renderer
  {
  public:
    OpenGLRenderer( void );
    virtual void beginRender( void ) override;
    virtual void clearBuffers( void ) override;
    virtual void endRender( void ) override;

    virtual const Viewport getViewport( void );

    virtual void setViewport( const Viewport& ) override;
    virtual void setBlendingState(
      const mb::PipelineState::BlendingState* );
    virtual void setCullState(
      const mb::PipelineState::CullFaceState* );
    virtual void setDepthState(
      const mb::PipelineState::DepthState* );
    virtual void setStencilState(
      const mb::PipelineState::StencilState* );
    virtual void setWireframeState(
      const mb::PipelineState::WireFrameState* );

    virtual void drawScreenQuad( void );
  protected:
    void configure( void );
  };
}

#endif /* __MB_OPENGL_RENDERER__ */
