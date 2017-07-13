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
