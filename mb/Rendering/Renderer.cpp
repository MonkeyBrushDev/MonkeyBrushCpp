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
  void Renderer::beginRender( BatchQueuePtr bq, RenderingPass* rp )
  {
    rp->beginRender( this, bq );
  }
  void Renderer::beginRenderToPrimitive( Primitive* p )
  {
     unsigned int nVBOs = 0;
     if( !p->getVertices().empty() )  ++nVBOs;
     if( !p->getNormals().empty() )   ++nVBOs;
     if( !p->getTexCoords().empty() ) ++nVBOs;
     if( !p->getIndices().empty() )   ++nVBOs;

      std::vector<uint32_t> VBO( nVBOs/*4*/ );
      unsigned int VAO;
      glGenVertexArrays( 1, &VAO );
      glBindVertexArray( VAO );
      glGenBuffers( 4, VBO.data( ) );

      glBindVertexArray( VAO );
      p->setVAO( VAO );

      unsigned int indexVBO = 0;

      //Vertices
      if( !p->getVertices().empty() )
      {
        glBindBuffer( GL_ARRAY_BUFFER, VBO[ indexVBO ] );
        glBufferData( GL_ARRAY_BUFFER, sizeof( Vector3 ) *p->getVertices().size( ),
                      p->getVertices().data( ), GL_STATIC_DRAW );
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, 0 );
        glEnableVertexAttribArray( 0 );

        indexVBO++;
      }

      //Normals
      if( !p->getNormals().empty() )
      {
        glBindBuffer( GL_ARRAY_BUFFER, VBO[ indexVBO ] );
        glBufferData( GL_ARRAY_BUFFER, sizeof( Vector3 ) *p->getNormals().size( ),
                      p->getNormals().data( ), GL_STATIC_DRAW );
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, 0 );
        glEnableVertexAttribArray( 1 );

        indexVBO++;
      }

      //Texture coordinates
      if( !p->getTexCoords().empty() )
      {
        glBindBuffer( GL_ARRAY_BUFFER, VBO[ indexVBO ] );
        glBufferData( GL_ARRAY_BUFFER, sizeof( Vector2 ) *p->getTexCoords().size( ),
                       p->getTexCoords().data( ), GL_STATIC_DRAW );
        glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 0, 0 );
        glEnableVertexAttribArray( 2 );

        indexVBO++;
      }

      //Strips
      if( !p->getIndices().empty() )
      {
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, VBO[ indexVBO ] );
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( GLushort )
                      *p->getIndices().size( ), p->getIndices().data( ), GL_STATIC_DRAW );
      }

      glBindVertexArray( 0 );

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

  void Renderer::drawPrimitive( /*MaterialPtr,*/ Primitive* p )
  {
    glBindVertexArray( p->getVAO() );

    switch( p->getTypeDraw() )
    {
      case Primitive::DRAW_ARRAYS:

        glDrawArrays( ((GLenum)p->getType()), 0, p->getMaxPoints() );

        break;
       case Primitive::DRAW_ELEMENTS:

         glDrawElements( ((GLenum)p->getType()),
                         sizeof( GLushort ) *p->getIndices().size( ),
           GL_UNSIGNED_SHORT, 0 );

         break;
       default:
         glDrawElements( ((GLenum)p->getType()),
                         sizeof( GLushort ) *p->getIndices().size( ),
           GL_UNSIGNED_SHORT, 0 );

         break;
     }

     glBindVertexArray( 0 );
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
