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

#ifndef __MB_RENDER_TARGET__
#define __MB_RENDER_TARGET__

#include <mb/api.h>
#include "Texture.hpp"

namespace mb
{
  class RenderTarget
  {
  public:
    enum class Type
    {
      RGB,
      RGBA
    };
    MB_API
    RenderTarget( unsigned int w, unsigned int h, RenderTarget::Type type,
      bool floatTexture = false )
      : _width( w )
      , _height( h )
      , _type( type )
      , _useFloatTexture( floatTexture )
      , _texture( nullptr ) // TODO
    {
    }
    MB_API
    virtual ~RenderTarget( void )
    {
      // TODO: Destroy texture??
    }
    MB_API
    RenderTarget::Type getRenderype( void ) const { return _type; }
    MB_API
    unsigned int getWidth( void ) const { return _width; }
    MB_API
    unsigned int getHeight( void ) const { return _height; }
    MB_API
    bool useFloatTexture( void ) const { return _useFloatTexture; }

    MB_API
    Texture* getTexture( void ) { return _texture; }
  protected:
    unsigned int _width;
    unsigned int _height;
    RenderTarget::Type _type;
    bool _useFloatTexture;
    Texture* _texture;
  };
}

#endif /* __MB_RENDER_TARGET__ */
