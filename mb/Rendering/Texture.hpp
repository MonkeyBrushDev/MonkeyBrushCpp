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

#ifndef __MB_TEXTURE__
#define __MB_TEXTURE__

#include <mb/api.h>
#include <string>

namespace mb
{
  class Texture
  {
  public:
    enum class WrapMode: short
    {
      REPEAT, CLAMP_TO_EDGE
    };
    enum class FilterMode: short
    {
      LINEAR, NEAREST
    };
    enum class FormatTexture: short
    {
      RGB, RGBA
    };
    MB_API
    WrapMode getWrapMode( void ) const { return _wrapMode; }
    MB_API
    void setWrapMode( const WrapMode& wm ) { _wrapMode = wm; }
    MB_API
    FilterMode getMinFilter( void ) const { return _minFilter; }
    MB_API
    void setMinFilter( const FilterMode& fm ) { _minFilter = fm; }
    MB_API
    FilterMode getMagFilter( void ) const { return _magFilter; }
    MB_API
    void setMagFilter( const FilterMode& fm ) { _magFilter = fm; }
    MB_API
    unsigned int getWidth( void ) const { return _width; }
    MB_API
    unsigned int getHeight( void ) const { return _height; }
    MB_API
    unsigned int getAnisoLevel( void ) const { return _anisoLevel; }
    MB_API
    void setAnisoLevel( unsigned int anisoLevel ) { _anisoLevel = anisoLevel; }

    MB_API
    void bind( int slot = -1 );
    MB_API
    void unbind( void );
  protected:
    Texture(unsigned int w, unsigned int h, FormatTexture format,
      bool linear, unsigned int target );
  protected:
    WrapMode _wrapMode;
    FilterMode _minFilter; // = FilterMode::LINEAR;
    FilterMode _magFilter; // = FilterMode::LINEAR;
    unsigned int _width;
    unsigned int _height;
    unsigned int _anisoLevel;
    unsigned int _target;
    unsigned int _handler;
  };
  class Texture1D: public Texture
  {
  public:
    MB_API
    Texture1D( unsigned int w );
    MB_API
    Texture1D( unsigned int w, Texture::FormatTexture format );
    MB_API
    Texture1D( unsigned int w, FormatTexture format, bool linear );
  };

  class Texture2DArray: public Texture
  {
  public:
    MB_API
    Texture2DArray( unsigned int w, unsigned int h, unsigned int d,
      FormatTexture format );
    MB_API
    Texture2DArray( unsigned int w, unsigned int h, unsigned int d,
      FormatTexture format, bool linear );
    MB_API
    unsigned int getDepth( void ) const { return _depth; }
    MB_API
    void setDepth( unsigned int d ) { _depth = d; }
    MB_API
    void apply( void ); // bool updateMipMaps = true
  protected:
    unsigned int _depth;
  };
  class Texture3D: public Texture
  {
  public:
    MB_API
    Texture3D( unsigned int w, unsigned int h, unsigned int d,
      FormatTexture format );
    MB_API
    Texture3D( unsigned int w, unsigned int h, unsigned int d,
      FormatTexture format, bool linear );
    MB_API
    unsigned int getDepth( void ) const { return _depth; }
    MB_API
    void setDepth( unsigned int d ) { _depth = d; }
    MB_API
    void apply( void ); // bool updateMipMaps = true
  protected:
    unsigned int _depth;
  };
  class Texture2D: public Texture
  {
  public:
    MB_API
    Texture2D( unsigned int w, unsigned int h );
    MB_API
    Texture2D( unsigned int w, unsigned int h, FormatTexture format );
    MB_API
    Texture2D( unsigned int w, unsigned int h, FormatTexture format,
      bool linear );
    MB_API
    void loadRawTexture( unsigned char* data );
    MB_API
    void loadImageTexture( const std::string& fileName );
    MB_API
    void apply( void ); // bool updateMipMaps = true
    MB_API
    static mb::Texture2D* loadFromImage( const std::string& fileName );
  protected:
    Texture2D( void ) : Texture2D( 0, 0 ) { }
    unsigned char* _data;
  };

  /*
  class Texture2D: public Texture
  {
  public:
    Texture2D( unsigned int width, unsigned int height )
    {
      Texture2D( width, height, GL_RGBA32F, true, false );
    }
    Texture2D( unsigned int width, unsigned int height, unsigned int format, bool mipmap )
    {
      Texture2D( width, height, format, mipmap, false );
    }
    Texture2D( unsigned int width, unsigned int height, unsigned int format, bool mipmap, bool linear )
      : Texture( width, height, format, mipmap, linear )
    {
      _filter = linear ? GL_LINEAR : GL_NEAREST;
    }
    // void setPixel( unsigned int x, unsigned int y, const mb::Color& color )
    // mb::Color getPixel( unsigned int x, unsigned int y )
    // void loadRawTexture( unsigned char * data )
    // void loadRawTexture( unsigned char * data, unsigned int size )}
  };*/
}

#endif /* __MB_TEXTURE__ */
