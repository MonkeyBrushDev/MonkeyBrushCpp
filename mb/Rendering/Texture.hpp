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

#include "../Includes.hpp"

#include <FreeImage.h>
#include <iostream>
#include <fstream>

#include "../Maths/Color.hpp"

namespace mb
{
  class Texture
  {

  };
  /*class Texture
  {
  public:
    bool _anisotropicFiltering;
    unsigned int _width; // ONLY GET
    unsigned int _height; // ONLY GET
    unsigned int _filterMode;
    unsigned int _anisoLevel;
    unsigned int _wrapMode;
    unsigned int _filter;
  protected:
    Texture( unsigned int width, unsigned int height, unsigned int format, bool mipmap, bool linear )
      : _width( width )
      , _height( height )
      , _filter
    {
      _filter = linear ? GL_LINEAR : GL_NEAREST;
    }
  };
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
  };
  class Texture2DArray: public Texture
  {
  public:
    Texture2DArray( unsigned int width, unsigned int height, unsigned int depth,
      unsigned int format, bool mipmap )
    {
      Texture2DArray( width, height, depth, format, mipmap, false );
    }
    Texture2DArray( unsigned int width, unsigned int height, unsigned int depth,
      unsigned int format, bool mipmap, bool linear )
      : Texture( width, height, format, mipmap, linear )
      , _depth( depth )
    {
    }
    void apply( bool updateMipmaps = true )
    {

    }
    unsigned int _depth;
  };
  class Texture3D: public Texture
  {
  public:
    Texture3D( unsigned int width, unsigned int height, unsigned int depth,
      unsigned int format, bool mipmap )
    {
      Texture3D( width, height, depth, format, mipmap, false );
    }
    Texture3D( unsigned int width, unsigned int height, unsigned int depth,
      unsigned int format, bool mipmap, bool linear )
      : Texture( width, height, format, mipmap, linear )
      , _depth( depth )
    {
    }
    void apply( bool updateMipmaps = true )
    {

    }
    unsigned int _depth;
  };*/
  class Texture2D
  {
  public:
    Texture2D( const std::string fileName )
    {
      const char* fileName_ = fileName.c_str();
      FreeImage_Initialise( TRUE );
      FREE_IMAGE_FORMAT format = FreeImage_GetFileType( fileName_, 0 );
      if ( format == FIF_UNKNOWN )
        format = FreeImage_GetFIFFromFilename( fileName_ );
      if ( ( format == FIF_UNKNOWN ) || !FreeImage_FIFSupportsReading( format ) )
        throw;
      FIBITMAP* img = FreeImage_Load( format, fileName_ );
      if ( img == nullptr )
        throw;
      FIBITMAP* tempImg = img;
      img = FreeImage_ConvertTo32Bits( img );
      FreeImage_Unload( tempImg );
      width_ = FreeImage_GetWidth( img );
      height_ = FreeImage_GetHeight( img );
      //BGRA a RGBA
      unsigned char * data = new unsigned char[ 4 * width_*height_ ];
      char *buff = ( char* ) FreeImage_GetBits( img );
      for ( unsigned int j = 0; j < width_*height_; ++j )
      {
        data[ j * 4 + 0 ] = buff[ j * 4 + 2 ];
        data[ j * 4 + 1 ] = buff[ j * 4 + 1 ];
        data[ j * 4 + 2 ] = buff[ j * 4 + 0 ];
        data[ j * 4 + 3 ] = buff[ j * 4 + 3 ];
      }
      FreeImage_Unload( img );
      FreeImage_DeInitialise( );


      glGenTextures( 1, &_handler );
      glBindTexture( GL_TEXTURE_2D, _handler );

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        width_,
        height_,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        data
      );
      glGenerateMipmap(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, 0);
    }
    void bind( int slot = -1 )
    {
      if ( slot >= 0 )
      {
        glActiveTexture( GL_TEXTURE0 + slot );
      }
      glBindTexture( GL_TEXTURE_2D, _handler );
    }
    void unbind( void )
    {
      glBindTexture( GL_TEXTURE_2D, -1 );
    }
  public:
    unsigned int _handler;
  protected:
    unsigned int width_;
    unsigned int height_;
  };
}

#endif /* __MB_TEXTURE__ */
