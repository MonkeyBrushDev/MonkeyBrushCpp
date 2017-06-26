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

#include "Texture.hpp"
#include "../Maths/Vector2.hpp"

namespace mb
{
  class RenderingPass;

  class Renderer
  {
  public:
    Renderer( void );
    virtual ~Renderer( void );

    virtual void setViewport( const Viewport& );
    virtual void beginRender( void );
    virtual void clearBuffers( void );
    virtual void endRender( void );

    virtual void render( BatchQueuePtr bq, RenderingPass* rp );

    //virtual void bindFramebuffer( FBO* f );
    //virtual void unbindFramebuffer( FBO* f );

    virtual void bindTexture( Texture* t );
    virtual void unbindTexture( Texture* t );

    virtual void drawPrimitive( MaterialPtr, Primitive* p );
    //virtual void drawBuffer( MaterialPtr , ... )
    virtual void drawScreenQuad( MaterialPtr );

    void setCullState( const mb::PipelineState::CullFaceState* cullState );
    void setDepthState( const mb::PipelineState::DepthState* depthState );
    void setBlendingState( const mb::PipelineState::BlendingState* blendState );
    void setStencilState( const mb::PipelineState::StencilState* stencilState );
    void setWireframeState( const mb::PipelineState::WireFrameState* wireState );

    const Viewport getViewport( void );

    const Vector2 getDepthRange( void );
    void setDepthRange( float zMin, float zMax );

    void clearColorBuffer( void );
    void clearDepthBuffer( void );
    void clearStencilBuffer( void );

    void setColorMask( bool allowRed, bool allowGreen,
      bool allowBlue, bool allowAlpha );

    //typedef std::map< const Texture*, TextureImpl* > TextureMap;
    //TextureMap _textureMap;
  };
}

#endif /* __MB_RENDERER__ */
