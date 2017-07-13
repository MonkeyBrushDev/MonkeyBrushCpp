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

#ifndef __MB_RENDER_BUFFER__
#define __MB_RENDER_BUFFER__

#include <mb/api.h>
#include "../Maths/Vector2.hpp"

namespace mb
{
  class RenderBuffer
  {
  public:
    MB_API
    virtual ~RenderBuffer( void );
    MB_API
    virtual void resize( const mb::Vector2& size ) = 0;
    MB_API
    void bind( void );
    MB_API
    void unbind( void );
  protected:
    RenderBuffer( const mb::Vector2& size, unsigned int format,
      unsigned int attachment, unsigned int samples = 4 );
    mb::Vector2 _size;
    unsigned int _format;
    unsigned int _attachment;
    unsigned int _samples;
    unsigned int _handler;
  };
  class RenderBufferTexture: public RenderBuffer
  {
  public:
    MB_API
    RenderBufferTexture( const mb::Vector2& size, unsigned int format,
      unsigned int attachment );
    MB_API
    virtual void resize( const mb::Vector2& size );
  };
  class RenderBufferMultisampleTexture: public RenderBuffer
  {
  public:
    MB_API
    RenderBufferMultisampleTexture(const mb::Vector2& size, unsigned int format,
      unsigned int attachment, unsigned int samples = 4);
    MB_API
    virtual void resize( const mb::Vector2& size );
  };
}

#endif /* __MB_RENDER_BUFFER__ */
