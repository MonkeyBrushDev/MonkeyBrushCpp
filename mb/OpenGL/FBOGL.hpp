#pragma once

#include "../Rendering/FramebufferObject.hpp"

#include "../Includes.hpp"

namespace mb
{
  namespace gl
  {
    class FBOResource
    {
    public:
      FBOResource( )
      {
        glGenFramebuffers( 1, &_handler );
      }
      virtual ~FBOResource( void ) { }
      virtual void bind( FramebufferObject* fbo )
      {
        glBindFramebuffer( GL_FRAMEBUFFER, _handler );
        glViewport( 0.0f, 0.0f, fbo->getWidth( ), fbo->getHeight( ) );

        const Color4& clearColor = fbo->getClearColor( );

        glClearColor( clearColor.r( ), clearColor.g( ), clearColor.b( ), clearColor.a( ) );
      }
      virtual void unbind( FramebufferObject* )
      {
        glBindFramebuffer( GL_FRAMEBUFFER, 0 );
      }
      virtual void load( FramebufferObject* )
      {

      }
      virtual void unload( FramebufferObject* )
      {

      }
      virtual void cleanup( void )
      {
        // TODO: Destroy textures
        glDeleteFramebuffers( 1, &_handler );
      }
    protected:
      unsigned int _handler;
    };
  }
}
