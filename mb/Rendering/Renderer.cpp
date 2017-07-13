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
  }
  Renderer::~Renderer( void )
  {
  }
  void Renderer::setViewport( const Viewport& )
  {
  }
  void Renderer::beginRender( void )
  {
  }
  void Renderer::clearBuffers( void )
  {
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

  void Renderer::drawPrimitive( MaterialPtr, Primitive* )
  {
    /*Primitive::Type type_ = p->getType( );
    unsigned int type = mb::gl::glOGLPrimitiveType[ ( short ) type_ ];
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
    }*/

    //glDrawElements( type, p->getNumIndex( ), GL_UNSIGNED_SHORT, 0 );
  }
  //virtual void drawBuffer( MaterialPtr , ... )
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


  /*MyFBO* Renderer::getFramebuffer( const std::string& name )
  {
    return _fbos[ name ];
  }*/
}
