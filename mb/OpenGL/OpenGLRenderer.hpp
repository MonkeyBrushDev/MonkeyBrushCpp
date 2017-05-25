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
    virtual void configure( void ) override;
    //OpenGLRenderer( );
    //~OpenGLRenderer( );
    virtual void setViewport( const Viewport& viewport );
    virtual void beginRender( void );
    virtual void clearBuffers( void );
    virtual void endRender( void );
  public:
    virtual void bindFBO( unsigned int fbo );
    virtual void unbindFBO( unsigned int fbo );

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
    void configureDepthState( mb::PipelineState::DepthState* st );
    void configureBlendState( mb::PipelineState::BlendingState* st );
    void configureCullFaceState( mb::PipelineState::CullFaceState* st );
    void configureColorMaskState( mb::PipelineState::ColorMaskState *st );
  };
}

#endif /* __MB_OPENGL_RENDERER__ */
