#include "OpenGLRenderer.hpp"

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
  void OpenGLRenderer::setViewport( const Viewport& viewport )
  {
    std::cout << "CHANGE VIEWPORT" << std::endl;
    glViewport(
      viewport.x( ), viewport.y( ), viewport.width( ), viewport.height( )
    );
  }
  void OpenGLRenderer::beginRender( void )
  {
    Renderer::beginRender( );
  }
  void OpenGLRenderer::clearBuffers( void )
  {
    std::cout << "Clear color and depth buffers" << std::endl;
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  }
  void OpenGLRenderer::endRender( void )
  {
    Renderer::endRender( );
  }
  void OpenGLRenderer::bindFBO( unsigned int fbo )
  {
    if ( fbo > 0 )
    {
      std::cout << "Bind FBO (" << fbo << ")" << std::endl;
    }
    else
    {
      std::cout << "Bind Default FBO" << std::endl;
    }
  }
  void OpenGLRenderer::unbindFBO( unsigned int fbo )
  {
    if ( fbo > 0 )
    {
      std::cout << "Unbind FBO (" << fbo << ")" << std::endl;
    }
    else
    {
      //std::cout << "Unbind Default FBO" << std::endl;
      std::cout << "Final Drawing into default fbo" << std::endl;
    }
  }

  void OpenGLRenderer::configureDepthState( mb::PipelineState::DepthState* st )
  {
    if ( st->isEnabled( ) )
    {
      glEnable( GL_DEPTH_TEST );

      /* TODO GLenum compareFunc = getDepthMode( ( short ) st->getCompareFunc( ) );
      glDepthFunc( compareFunc );

      glDepthMask( st->isWritable( ) );*/
    }
    else
    {
      glDisable( GL_DEPTH_TEST );
    }
  }
  void OpenGLRenderer::configureBlendState( mb::PipelineState::BlendingState* st )
  {
    if ( st->isEnabled( ) )
    {
      glEnable( GL_BLEND );
    }
    else
    {
      glDisable( GL_BLEND );
    }
  }
  void OpenGLRenderer::configureCullFaceState( mb::PipelineState::CullFaceState* st )
  {
    if ( st->isEnabled( ) )
    {
      glEnable( GL_CULL_FACE );

      GLenum mode = getCullFaceMode( ( short ) st->getCullFaceMode( ) );
      glCullFace( mode );
    }
    else
    {
      glDisable( GL_CULL_FACE );
    }
  }
  void OpenGLRenderer::configureColorMaskState( mb::PipelineState::ColorMaskState *st )
  {
    if ( st->isEnabled( ) )
    {
      glColorMask(
        st->isRMask( ), st->isGMask( ), st->isBMask( ), st->isAMask( )
      );
    }
    else {
      glColorMask( GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE );
    }
  }
}
