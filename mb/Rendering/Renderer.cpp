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

#include "Renderer.hpp"
#include "RenderPasses/RenderingPass.hpp"
#include "BatchQueue.hpp"
#include "../Scenegraph/Camera.hpp"

#include "../Includes.hpp"



#include <GL/glew.h>
#include "../Maths/Rect.hpp"

namespace mb
{
  Renderer::Renderer( void )
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

  //std::cout << "VAO: " << VAO << " - VBO: " << VBO << std::endl;
  }

  Renderer::~Renderer( void )
  {

  }

  void Renderer::setViewport( const Viewport& viewport )
  {
    //std::cout << "CHANGE VIEWPORT" << std::endl;
    glViewport(
      viewport.x( ), viewport.y( ),
      viewport.width( ), viewport.height( )
    );
  }
  void Renderer::beginRender( void )
  {

  }
  void Renderer::clearBuffers( void )
  {
    //std::cout << "Clear color and depth buffers" << std::endl;
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  }
  void Renderer::endRender( void )
  {

  }

  void Renderer::render( BatchQueuePtr bq, RenderingPass* rp )
  {
    rp->render( this, bq, bq->getCamera( ) );
  }

  /*void Renderer::bindFramebuffer( FBO* f )
  {

  }
  void Renderer::unbindFramebuffer( FBO* f )
  {

  }*/

  void Renderer::bindTexture( Texture* t )
  {
    if ( t == nullptr ) return;
  }
  void Renderer::unbindTexture( Texture* t )
  {
    if ( t == nullptr ) return;
  }

  void Renderer::drawPrimitive( MaterialPtr m, Primitive* p )
  {
    Primitive::Type type_ = p->getType( );
    unsigned int type = 0;
    switch ( type_ )
    {
      case Primitive::Type::POINTS:
        type = GL_POINTS;
        break;
      case Primitive::Type::LINES:
        type = GL_LINES;
        break;
      case Primitive::Type::TRIANGLES:
        type = GL_TRIANGLES;
        break;
      case Primitive::Type::TRIANGLE_FAN:
        type = GL_TRIANGLE_FAN;
        break;
      case Primitive::Type::TRIANGLE_STRIP:
        type = GL_TRIANGLE_STRIP;
        break;
    }

    //glDrawElements( type, p->getNumIndex( ), GL_UNSIGNED_SHORT, 0 );
  }
  //virtual void drawBuffer( MaterialPtr , ... )
  void Renderer::drawScreenQuad( MaterialPtr m )
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
    m->use( );
    glBindVertexArray( VAO );
    glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );
    glBindVertexArray( 0 );
    m->unuse( );
  }
  void Renderer::setBlendingState( const mb::PipelineState::BlendingState* blendState )
  {
    if ( blendState->isEnabled( ) )
    {
      static GLenum glSrcBlend[ 11 ] =
      {
        GL_ZERO,
        GL_ONE,
        GL_SRC_COLOR,
        GL_ONE_MINUS_SRC_COLOR,
        GL_DST_COLOR,
        GL_ONE_MINUS_DST_COLOR,
        GL_SRC_ALPHA,
        GL_ONE_MINUS_SRC_ALPHA,
        GL_DST_ALPHA,
        GL_ONE_MINUS_DST_ALPHA,
        GL_SRC_ALPHA_SATURATE,
      };
      static GLenum glDstBlend[ 8 ] =
      {
        GL_ZERO,
        GL_ONE,
        GL_SRC_COLOR,
        GL_ONE_MINUS_SRC_COLOR,
        GL_SRC_ALPHA,
        GL_ONE_MINUS_SRC_ALPHA,
        GL_DST_ALPHA,
        GL_ONE_MINUS_DST_ALPHA,
      };
      unsigned int srcBlend = glSrcBlend[ ( short ) blendState->getSourceFunc( ) ];
      unsigned int dstBlend = glDstBlend[ ( short ) blendState->getDstFunc( ) ];
      glEnable( GL_BLEND );
      glBlendFunc( srcBlend, dstBlend );
    }
    else
    {
      glDisable( GL_BLEND );
    }
  }
  void Renderer::setCullState( const mb::PipelineState::CullFaceState* cullState )
  {
    if ( cullState->isEnabled( ) )
    {
      glEnable( GL_CULL_FACE );

      static GLenum gCullMode[ 3 ] =
      {
        GL_FRONT,
        GL_BACK,
        GL_FRONT_AND_BACK,
      };
      GLenum cullMode = gCullMode[ ( short ) cullState->getCullFaceMode( ) ];
      glCullFace( cullMode );
    }
    else
    {
      glDisable( GL_CULL_FACE );
    }
  }
  void Renderer::setDepthState( const mb::PipelineState::DepthState* depthState )
  {
    if ( depthState->isEnabled( ) )
    {
      glEnable( GL_DEPTH_TEST );
    }
    else
    {
      glDisable( GL_DEPTH_TEST );
    }
    static GLenum gDepthCompareFunc[ 8 ] =
    {
      GL_NEVER,
      GL_LESS,
      GL_EQUAL,
      GL_LEQUAL,
      GL_GREATER,
      GL_NOTEQUAL,
      GL_GEQUAL,
      GL_ALWAYS
    };
    GLenum compareFunc = gDepthCompareFunc[ ( short ) depthState->compare ];
    glDepthFunc( compareFunc );
    glDepthMask( depthState->writable ? GL_TRUE : GL_FALSE );
  }
  void Renderer::setStencilState( const mb::PipelineState::StencilState* stencilState )
  {
    if ( stencilState->isEnabled( ) )
    {
      glEnable( GL_STENCIL_TEST );

      static GLenum gStencilCompare[ 8 ] =
      {
        GL_NEVER, GL_LESS, GL_EQUAL, GL_LEQUAL,
        GL_GREATER, GL_NOTEQUAL, GL_GEQUAL, GL_ALWAYS,
      };
      static GLenum gStencilOperation[ 6 ] =
      {
        GL_KEEP, GL_ZERO, GL_REPLACE,
        GL_INCR, GL_DECR, GL_INVERT,
      };
      unsigned int compare = gStencilCompare[ ( short ) stencilState->Compare ];
      glStencilFunc( compare, stencilState->Reference, stencilState->Mask );
      glStencilMask( stencilState->WriteMask );

      GLenum onFail = gStencilOperation[ ( short ) stencilState->OnFail ];
      GLenum onZFail = gStencilOperation[ ( short ) stencilState->OnZFail ];
      GLenum onZPass = gStencilOperation[ ( short ) stencilState->OnZPass ];
      glStencilOp( onFail, onZFail, onZPass );
    }
    else
    {
      glDisable( GL_STENCIL_TEST );
    }
  }
  void Renderer::setWireframeState( const mb::PipelineState::WireFrameState* wireState )
  {
    if ( wireState->isEnabled( ) )
    {
      glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    }
    else
    {
      glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    }
  }
  const Viewport Renderer::getViewport( void )
  {
    int params[ 4 ];
    glGetIntegerv( GL_VIEWPORT, params );

    return Viewport( params[ 0 ], params[ 1 ], params[ 2 ], params[ 3 ] );
  }
  const Vector2 Renderer::getDepthRange( void )
  {
    GLclampd params[ 2 ];
    glGetDoublev( GL_DEPTH_RANGE, params );

    return Vector2( params[ 0 ], params[ 1 ] );
  }
  void Renderer::setDepthRange( float zMin, float zMax )
  {
    glDepthRange( ( GLclampd ) zMin, ( GLclampd ) zMax );
  }

  void Renderer::clearColorBuffer( void )
  {
    //glClearColor( mClearColor[ 0 ], mClearColor[ 1 ], mClearColor[ 2 ], mClearColor[ 3 ] );

    glClear( GL_COLOR_BUFFER_BIT );
  }
  void Renderer::clearDepthBuffer( void )
  {
    //glClearDepth( ( GLclampd ) mClearDepth );

    glClear( GL_DEPTH_BUFFER_BIT );
  }
  void Renderer::clearStencilBuffer( void )
  {
    //glClearStencil( ( GLint ) mClearStencil );

    glClear( GL_STENCIL_BUFFER_BIT );
  }
  void Renderer::setColorMask( bool allowRed, bool allowGreen,
    bool allowBlue, bool allowAlpha )
  {
    GLboolean rMask = ( allowRed ? 1 : 0 );
    GLboolean gMask = ( allowGreen ? 1 : 0 );
    GLboolean bMask = ( allowBlue ? 1 : 0 );
    GLboolean aMask = ( allowAlpha ? 1 : 0 );
    glColorMask( rMask, gMask, bMask, aMask );
  }
}
