#include "Framebuffer.hpp"

#include "../Includes.hpp"

namespace mb
{
  RenderTarget::RenderTarget( Type t, Output o, 
    uint32_t w, uint32_t h, bool useFloat )
    : _type( t )
    , _output( o )
    , _width( w )
    , _height( h )
    , _texture( nullptr )
    , _floatTexture( useFloat )
  {
  }

  Framebuffer::Framebuffer( uint32_t w, uint32_t h )
    : _width ( w )
    , _height( h )
    , _clearColor( mb::Color::BLACK )
  {
  }

  StandardFramebuffer::StandardFramebuffer( uint32_t w, uint32_t h )
    : Framebuffer( w, h )
  {
    _targets.push_back( std::make_shared<RenderTarget>( 
      RenderTarget::Type::COLOR_RGBA, RenderTarget::Output::TEXTURE, w, h, true )
    );
    _targets.push_back( std::make_shared<RenderTarget>( 
      RenderTarget::Type::DEPTH, RenderTarget::Output::RENDER, w, h, true )
    );

    create( );
  }

  void Framebuffer::create( )
  {
    glCreateFramebuffers( 1, &_fbo );
    glBindFramebuffer( GL_FRAMEBUFFER, _fbo );

    int colorAttachmentOffset = 0;
    for ( RenderTargetPtr target : _targets )
    {
      uint32_t targetWidth = target->_width;
      uint32_t targetHeight = target->_height;

      GLenum internalFormat = GL_INVALID_ENUM;
      GLenum attachment = GL_INVALID_ENUM;
      GLenum textureType = target->_floatTexture ? 
          GL_FLOAT : GL_UNSIGNED_BYTE;
      GLenum textureFormat = GL_RGBA;
      switch ( target->_type )
      {
        case RenderTarget::Type::COLOR_RGB:
          internalFormat = target->_floatTexture ? GL_RGB16F : GL_RGB;
          textureFormat = GL_RGB;
          attachment = GL_COLOR_ATTACHMENT0 + colorAttachmentOffset++;
          break;
        case RenderTarget::Type::COLOR_RGBA:
          internalFormat = target->_floatTexture ? GL_RGBA16F : GL_RGBA;
          textureFormat = GL_RGBA;
          attachment = GL_COLOR_ATTACHMENT0 + colorAttachmentOffset++;
          break;
        case RenderTarget::Type::DEPTH:
          internalFormat = target->_floatTexture ? 
              GL_DEPTH_COMPONENT32F : GL_DEPTH_COMPONENT32;
          attachment = GL_DEPTH_ATTACHMENT;
          textureFormat = GL_DEPTH_COMPONENT;
          break;
      }

      if ( internalFormat != GL_INVALID_ENUM && attachment != GL_INVALID_ENUM )
      {
        if ( target->_output == RenderTarget::Output::RENDER )
        {
          GLuint renderBufferId;
          glGenRenderbuffers( 1, &renderBufferId );

          glBindRenderbuffer( GL_RENDERBUFFER, renderBufferId );
          glRenderbufferStorage( GL_RENDERBUFFER, internalFormat, 
            targetWidth, targetHeight );
          glFramebufferRenderbuffer( GL_FRAMEBUFFER, attachment, 
            GL_RENDERBUFFER, renderBufferId );
        }
        if ( target->_output == RenderTarget::Output::TEXTURE )
        {

        }
        uint32_t textureID;
        glGenTextures( 1, &textureID );
        glBindTexture( GL_TEXTURE_2D, textureID );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
        glTexImage2D( GL_TEXTURE_2D, 0, internalFormat, 
          targetWidth, targetHeight, 0, textureFormat, textureType, 0 );
        glFramebufferTexture2D( GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, 
          textureID, 0 );
      }
    }

    GLenum status = glCheckFramebufferStatus( GL_FRAMEBUFFER );
    if ( status != GL_FRAMEBUFFER_COMPLETE )
    {
      throw;
    }
  }
  void Framebuffer::bind( void )
  {
    glBindFramebuffer( GL_FRAMEBUFFER, _fbo );
    //glViewport( 0.0f, 0.0f, _width, _height );
    
    const GLenum fboBuffers[ ] = {
      GL_COLOR_ATTACHMENT0,
      GL_COLOR_ATTACHMENT1,
      GL_COLOR_ATTACHMENT2,
      GL_COLOR_ATTACHMENT3,
      GL_COLOR_ATTACHMENT4,
      GL_COLOR_ATTACHMENT5,
      GL_COLOR_ATTACHMENT6,
      GL_COLOR_ATTACHMENT7,
    };
    
    int colorCount = 0;
    for ( const auto& target : _targets )
    {
      if ( target->_type == RenderTarget::Type::COLOR_RGB
        || target->_type == RenderTarget::Type::COLOR_RGBA )
      {
        ++colorCount;
      }
    }
    if ( colorCount > 0 )
    {
      glDrawBuffers( colorCount, fboBuffers );
    }
    else
    {
      glDrawBuffer( GL_NONE );
    }
    glClearColor( _clearColor.r( ), _clearColor.g( ), 
      _clearColor.b( ), _clearColor.a( ) );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  }

  void Framebuffer::unbind( void )
  {
    int defaultFBO = 0;

    glBindFramebuffer( GL_FRAMEBUFFER, defaultFBO );

    //glViewport( 0.0f, 0.0f, _width, _height );
  }
}
