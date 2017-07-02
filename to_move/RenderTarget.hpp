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
#include <map>
#include "Texture.hpp"
#include "../Includes.hpp"

namespace mb
{
  class RenderTarget
  {
  public:
    MB_API
    RenderTarget( unsigned int w, unsigned int h, unsigned int type,
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
    unsigned int getRenderype( void ) const { return _type; }
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
    unsigned int _type;
    bool _useFloatTexture;
    Texture* _texture;
  };
  class FBO
  {
  public:
    FBO( int w, int h )
      : _width( w )
      , _height( h )
    {

    }
    virtual ~FBO( void );

  protected:
    int _width;
    int _height;
    std::map< std::string, RenderTarget *> _renderTargets;
  };
  class BasicFBO: public FBO
  {
    BasicFBO( int w, int h )
      : FBO( w, h )
    {
      _renderTargets[ "fbo_color" ] =
        new RenderTarget( GL_RGBA, _width, _height );
      _renderTargets[ "fbo_depth" ] =
        new RenderTarget( GL_DEPTH, _width, _height );
    }
  };
}

#endif /* __MB_RENDER_TARGET__ */
