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

#include "OpenGLRenderer.hpp"

#include "../Rendering/Renderer.hpp"

#include "../Scenegraph/Camera.hpp"
#include "../Scenegraph/Geometry.hpp"

#include "../Maths/Rect.hpp"

#include <vector>
#include "../Rendering/Material.hpp"
#include "../Rendering/BatchQueue.hpp"

#include <GL/glew.h>

#include "OpenGLMapping.hpp"

namespace mb
{
  OpenGLRenderer::OpenGLRenderer( void )
    : Renderer( )
  {
    configure( );
  }
  void OpenGLRenderer::configure( void )
  {
    glewExperimental = GL_TRUE;
    if ( glewInit( ) != GLEW_OK )
    {
      throw;
    }

    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LEQUAL );
    glEnable( GL_CULL_FACE );
    glCullFace( GL_BACK );

    int defaultFBO;
    glGetIntegerv( GL_FRAMEBUFFER_BINDING, &defaultFBO );
    std::cout << "DEFAULT FBO AT " << defaultFBO << std::endl;
  }

  void OpenGLRenderer::beginRender( BatchQueuePtr bq , RenderingPass *rp )
  {
    Renderer::beginRender( bq, rp );
  }

  void OpenGLRenderer::endRender( void )
  {
    Renderer::endRender( );
  }

  void OpenGLRenderer::setViewport( const Viewport& viewport )
  {
    //std::cout << "CHANGE VIEWPORT" << std::endl;
    glViewport(
      viewport.x( ), viewport.y( ),
      viewport.width( ), viewport.height( )
    );
  }
  void OpenGLRenderer::clearBuffers( void )
  {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  }


  void OpenGLRenderer::setBlendingState( const mb::PipelineState::BlendingState* blendState )
  {
    if ( blendState->isEnabled( ) )
    {
      unsigned int srcBlend = mb::gl::glOGLSrcBlend[ ( short ) blendState->getSourceFunc( ) ];
      unsigned int dstBlend = mb::gl::glOGLDstBlend[ ( short ) blendState->getDstFunc( ) ];
      glEnable( GL_BLEND );
      glBlendFunc( srcBlend, dstBlend );
    }
    else
    {
      glDisable( GL_BLEND );
    }
  }
  void OpenGLRenderer::setCullState( const mb::PipelineState::CullFaceState* cullState )
  {
    if ( cullState->isEnabled( ) )
    {
      glEnable( GL_CULL_FACE );

      GLenum cullMode = mb::gl::glOGLCullMode[ ( short ) cullState->getCullFaceMode( ) ];
      glCullFace( cullMode );
    }
    else
    {
      glDisable( GL_CULL_FACE );
    }
  }
  void OpenGLRenderer::setDepthState( const mb::PipelineState::DepthState* depthState )
  {
    if ( depthState->isEnabled( ) )
    {
      glEnable( GL_DEPTH_TEST );
    }
    else
    {
      glDisable( GL_DEPTH_TEST );
    }
    GLenum compareFunc = mb::gl::glOGLDepthCompare[ ( short ) depthState->compare ];
    glDepthFunc( compareFunc );
    glDepthMask( depthState->writable ? GL_TRUE : GL_FALSE );
  }
  void OpenGLRenderer::setStencilState( const mb::PipelineState::StencilState* stencilState )
  {
    if ( stencilState->isEnabled( ) )
    {
      glEnable( GL_STENCIL_TEST );

      unsigned int compare = mb::gl::glOGLStencilCompare[ ( short ) stencilState->Compare ];
      glStencilFunc( compare, stencilState->Reference, stencilState->Mask );
      glStencilMask( stencilState->WriteMask );

      GLenum onFail = mb::gl::glOGLStencilOperation[ ( short ) stencilState->OnFail ];
      GLenum onZFail = mb::gl::glOGLStencilOperation[ ( short ) stencilState->OnZFail ];
      GLenum onZPass = mb::gl::glOGLStencilOperation[ ( short ) stencilState->OnZPass ];
      glStencilOp( onFail, onZFail, onZPass );
    }
    else
    {
      glDisable( GL_STENCIL_TEST );
    }
  }
  void OpenGLRenderer::setWireframeState( const mb::PipelineState::WireFrameState* wireState )
  {
    if ( wireState->isEnabled( ) )
    {
      glPolygonMode( GL_FRONT_AND_BACK, mb::gl::glOGLWireMode[ 0 ] );
    }
    else
    {
      glPolygonMode( GL_FRONT_AND_BACK, mb::gl::glOGLWireMode[ 1 ] );
    }
  }

  void OpenGLRenderer::drawScreenQuad( /*MaterialPtr m*/ )
  {
    static unsigned int VAO = -1;
    static unsigned int VBO;
    if ( (int)VAO == -1 )
    {
      float quadVertices[ ] = {
        -1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 0.0f
      };
      glGenVertexArrays( 1, &VAO );
      glGenBuffers( 1, &VBO );
      glBindVertexArray( VAO );
      glBindBuffer( GL_ARRAY_BUFFER, VBO );
      glBufferData( GL_ARRAY_BUFFER, sizeof( quadVertices ), &quadVertices, GL_STATIC_DRAW );
      glEnableVertexAttribArray( 0 );
      glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( GLfloat ), 0 );
    }
    //m->use( );
    glBindVertexArray( VAO );
    glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );
    glBindVertexArray( 0 );
    //m->unuse( );
  }


  const Viewport OpenGLRenderer::getViewport( void )
  {
    int params[ 4 ];
    glGetIntegerv( GL_VIEWPORT, params );

    return Viewport( params[ 0 ], params[ 1 ], params[ 2 ], params[ 3 ] );
  }
}
