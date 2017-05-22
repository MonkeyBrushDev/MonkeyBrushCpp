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
    virtual void drawPrimitive( MaterialPtr  material, Primitive* primitive ) { }

    // virtual void drawBuffer( Material* material ... ) { }
  };

}

#include <GL/glew.h>

namespace mb
{
  class OpenGLRenderer: public Renderer
  {
  public:
    virtual void configure( void ) override
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
    //OpenGLRenderer( );
    //~OpenGLRenderer( );
    virtual void setViewport( const Viewport& viewport )
    {
      std::cout << "CHANGE VIEWPORT" << std::endl;
      glViewport(
        viewport.x( ), viewport.y( ), viewport.width( ), viewport.height( )
      );
    }
    virtual void beginRender( void )
    {
      Renderer::beginRender( );
    }
    virtual void clearBuffers( void )
    {
      std::cout << "Clear color and depth buffers" << std::endl;
      glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    }
    virtual void endRender( void )
    {
      Renderer::endRender( );
    }
  public:
    virtual void bindFBO( unsigned int fbo )
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
    virtual void unbindFBO( unsigned int fbo )
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

    virtual void drawPrimitive( MaterialPtr  /*material*/, Primitive* primitive )
    {
      std::string type;
      switch ( primitive->_type )
      {
        case Primitive::Type::POINTS:
          type = "POINTS";
          break;
        case Primitive::Type::LINES:
          type = "LINES";
          break;
        case Primitive::Type::TRIANGLES:
        default:
          type = "TRIANGLES";
          break;
      }

      // glDrawElements( type, primitive->indexBuffer( )->count( ), GL_UNSIGNED_SHORT, 0) );
    }
  protected:
    GLenum getPrimitiveType( short type )
    {
      static std::vector<GLenum> primitive_types = {
        GL_POINTS,
        GL_LINES,
        GL_LINE_LOOP,
        GL_LINE_STRIP,
        GL_TRIANGLES,
        GL_TRIANGLE_FAN,
        GL_TRIANGLE_STRIP
      };
      return primitive_types[ type ];
    }
    GLenum getCullFaceMode( short mode )
    {
      static std::vector<GLenum> cullface_types = {
        GL_FRONT,
        GL_BACK,
        GL_FRONT_AND_BACK
      };
      return cullface_types[ mode ];
    }
    GLenum getDepthMode( short mode )
    {
      static std::vector<GLenum> depth_mode_types = {
        GL_NEVER,
        GL_LESS,
        GL_EQUAL,
        GL_LEQUAL,
        GL_GREATER,
        GL_NOTEQUAL,
        GL_GEQUAL,
        GL_ALWAYS
      };
      return depth_mode_types[ mode ];
    }
    void configureDepthState( mb::PipelineState::DepthState* st )
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
    void configureBlendState( mb::PipelineState::BlendingState* st )
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
    void configureCullFaceState( mb::PipelineState::CullFaceState* st )
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
    void configureColorMaskState( mb::PipelineState::ColorMaskState *st )
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
  };
}

#endif /* __MB_RENDERER__ */
