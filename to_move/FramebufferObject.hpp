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

#ifndef __MB_FRAMEBUFFER_OBJECT__
#define __MB_FRAMEBUFFER_OBJECT__

#include <mb/api.h>
#include "../Maths/Color.hpp"
#include "RenderTarget.hpp"

#include <map>

namespace mb
{
  class FramebufferObject
  {
  public:
    MB_API
    FramebufferObject( unsigned int width, unsigned int height );
    MB_API
    virtual ~FramebufferObject( void ) { }

    MB_API
    unsigned int getWidth( void ) const { return _width; }
    MB_API
    unsigned int getHeight( void ) const { return _height; }

    MB_API
    void resize( unsigned int w, unsigned int h );

    MB_API
    const mb::Color& getClearColor( void ) const { return _clearColor; }
    MB_API
    void setClearColor( const mb::Color& color ) { _clearColor = color; }


    const std::map< std::string, RenderTarget >& getRenderTargets( void ) const
    {
      return _renderTargets;
    }

  protected:
    unsigned int _width;
    unsigned int _height;
    mb::Color _clearColor;
    std::map< std::string, RenderTarget > _renderTargets;
  };

  class StandardFramebuffer: public FramebufferObject
  {
  public:
    MB_API
    StandardFramebuffer( unsigned int w, unsigned int h );
    MB_API
    virtual ~StandardFramebuffer( void );
  };

  class GBuffer: public FramebufferObject
  {
  public:
    MB_API
    GBuffer( unsigned int w, unsigned int h );
    MB_API
    virtual ~GBuffer( void );
  };
}

#endif /* __MB_FRAMEBUFFER_OBJECT__ */
