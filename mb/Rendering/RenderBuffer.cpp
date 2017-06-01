#include "RenderBuffer.hpp"
#include "../Includes.hpp"

namespace mb
{
  RenderBuffer::RenderBuffer( const mb::Vector2& size, unsigned int format,
    unsigned int attachment, unsigned int samples )
  : _size(size)
  , _format(format)
  , _attachment(attachment)
  , _samples(samples)
  {
    glCreateRenderbuffers( 1, &_handler );
  }
  RenderBuffer::~RenderBuffer()
  {
    glDeleteRenderbuffers( 1, &_handler );
  }
  void RenderBuffer::bind()
  {
    glBindRenderbuffer( GL_RENDERBUFFER, _handler );
  }
  void RenderBuffer::unbind()
  {
    glBindRenderbuffer( GL_RENDERBUFFER, 0 );
  }

  RenderBufferTexture::RenderBufferTexture( const mb::Vector2& size,
    unsigned int format, unsigned int attachment )
  : RenderBuffer(size, format, attachment)
  {
    this->bind();
    glRenderbufferStorage(GL_RENDERBUFFER, _format,
      (unsigned int)_size.x(), (unsigned int)size.y());
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, _attachment,
      GL_RENDERBUFFER, _handler);
    this->unbind();
  }
  void RenderBufferTexture::resize( const mb::Vector2& size )
  {
    this->bind();
    glRenderbufferStorage(GL_RENDERBUFFER, _format,
      (unsigned int)_size.x(), (unsigned int)size.y());
    this->unbind();
  }

  RenderBufferMultisampleTexture::RenderBufferMultisampleTexture(
    const mb::Vector2& size, unsigned int format,
    unsigned int attachment, unsigned int samples )
    : RenderBuffer(size, format, attachment, samples)
  {
    this->bind( );
    glRenderbufferStorageMultisample( GL_RENDERBUFFER, _samples, _format,
      (unsigned int)_size.x( ), (unsigned int)size.y( ) );
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, _attachment,
      GL_RENDERBUFFER, _handler);
    this->unbind( );
  }
  void RenderBufferMultisampleTexture::resize( const mb::Vector2& size )
  {
    this->bind( );
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, _samples,
      _format, (unsigned int)_size.x(), (unsigned int)size.y());
    this->unbind( );
  }
}
