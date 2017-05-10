#ifndef __MB_RENDERER__
#define __MB_RENDERER__

#include "../Scenegraph/Camera.hpp"
#include "../Scenegraph/Geometry.hpp"

#include <vector>
#include "Material.hpp"

namespace mb
{
  class RenderingPass;
  class BatchQueue;

  class Renderer
  {
  public:
    Renderer( );
    ~Renderer( );
    virtual void setViewport ( std::vector< float > ) { }
    virtual void beginRender( void );
    virtual void clearBuffers( void ) = 0;
    virtual void render( BatchQueue* rq, RenderingPass* rp );
    virtual void endRender( void );
  public:
    virtual void bindFBO( unsigned int ) { }
    virtual void unbindFBO( unsigned int ) { }
    virtual void drawPrimitive( Material* material, Primitive* primitive ) { }
    // virtual void drawBuffer( Material* material ... ) { }
  };


  class OpenGLRenderer: public Renderer
  {
  public:
    //OpenGLRenderer( );
    //~OpenGLRenderer( );
    virtual void setViewport( std::vector< float > )
    {
      std::cout << "CHANGE VIEWPORT" << std::endl;
    }
    virtual void beginRender( void )
    {
      Renderer::beginRender( );
    }
    virtual void clearBuffers( void )
    {
      std::cout << "Clear color and depth buffers" << std::endl;
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

    virtual void drawPrimitive( Material* material, Primitive* primitive )
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
  };
}

#endif /* __MB_RENDERER__ */
