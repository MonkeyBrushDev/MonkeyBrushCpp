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

#include "Texture.hpp"

#include "../Includes.hpp"

#include <FreeImage.h>
#include <iostream>
#include <fstream>

#include "../Utils/FileSystem.hpp"
#include "../Exceptions/RuntimeException.hpp"

namespace mb
{
  Texture::Texture(unsigned int w, unsigned int h, FormatTexture format,
    bool linear, unsigned int target )
    : _wrapMode( WrapMode::CLAMP_TO_EDGE )
    , _minFilter( linear? FilterMode::BILINEAR : FilterMode::NONE )
    , _magFilter( _minFilter )
    , _width( w )
    , _height( h )
    //, _anisoLevel( 0 )
    , _target( target )
    , _data( nullptr )
  {
    glGenTextures( 1, &_handler );

    switch( format )
    {
      case FormatTexture::R8:
        _type = GL_UNSIGNED_BYTE;
        _internalFormat = GL_R8;
        _format = GL_RED;
        break;
      case FormatTexture::R16F:
        _type = GL_UNSIGNED_BYTE;
        _internalFormat = GL_R16F;
        _format = GL_RED;
        break;
      case FormatTexture::RG8:
        _type = GL_UNSIGNED_BYTE;
        _internalFormat = GL_RG8;
        _format = GL_RG;
        break;
      case FormatTexture::RG32F:
        _type = GL_FLOAT;
        _internalFormat = GL_RG32F;
        _format = GL_RG;
        break;
      case FormatTexture::RGB:
        _type = GL_UNSIGNED_BYTE;
        _internalFormat = GL_RGB;
        _format = GL_RGB;
        break;
      case FormatTexture::RGBA:
        _type = GL_UNSIGNED_BYTE;
        _internalFormat = GL_RGBA;
        _format = GL_RGBA;
        break;
      case FormatTexture::RGB16F:
        _type = GL_FLOAT;
        _internalFormat = GL_RGB16F;
        _format = GL_RGB;
        break;
      case FormatTexture::RGBA16F:
        _type = GL_FLOAT;
        _internalFormat = GL_RGBA16F;
        _format = GL_RGBA;
        break;
      case FormatTexture::RGBA32F:
        _type = GL_FLOAT;
        _internalFormat = GL_RGBA32F;
        _format = GL_RGBA;
        break;
    }
  }
  void Texture::bind( int slot )
  {
    if ( slot >= 0 )
    {
      glActiveTexture( GL_TEXTURE0 + slot );
    }
    glBindTexture( _target, _handler );
  }
  void Texture::unbind( void )
  {
    glBindTexture( _target, 0 );
  }
  Texture::~Texture( void )
  {
    glDeleteTextures( 1, &_handler );
  }
}

namespace mb
{
  Texture1D::Texture1D( unsigned int w )
    : Texture1D( w, Texture::FormatTexture::RGBA, true )
  {
  }
  Texture1D::Texture1D( unsigned int w, Texture::FormatTexture format )
    : Texture1D( w, format, true )
  {
  }
  Texture1D::Texture1D( unsigned int w, FormatTexture format,
    bool linear )
    : Texture( w, 1, format, linear, GL_TEXTURE_1D )
  {
  }
  void Texture1D::apply( void )
  {
    this->bind( );
    glTexParameteri( _target, GL_TEXTURE_WRAP_S,
      getWrapMode( ) == WrapMode::CLAMP_TO_EDGE ? GL_CLAMP_TO_EDGE : GL_REPEAT );
    glTexParameteri( _target, GL_TEXTURE_WRAP_T,
      getWrapMode( ) == WrapMode::CLAMP_TO_EDGE ? GL_CLAMP_TO_EDGE : GL_REPEAT );
    glTexParameteri( _target, GL_TEXTURE_MIN_FILTER,
      getMinFilter( ) == FilterMode::BILINEAR ? GL_LINEAR : GL_NEAREST );
    glTexParameteri( _target, GL_TEXTURE_MAG_FILTER,
      getMagFilter( ) == FilterMode::BILINEAR ? GL_LINEAR : GL_NEAREST );

    glTexImage1D(
      this->_target,
      0, // level
      _internalFormat,    // internalFormat
      this->getWidth( ),
      0, // border
      _format, // format
      _type, // type
      _data
    );

    this->unbind( );
  }
}


namespace mb
{
  Texture2D::Texture2D( unsigned int w, unsigned int h )
    : Texture2D( w, h, Texture::FormatTexture::RGBA, true )
  {
  }
  Texture2D::Texture2D( unsigned int w, unsigned int h,
    FormatTexture format )
    : Texture2D( w, h, format, true )
  {
  }
  Texture2D::Texture2D( unsigned int w, unsigned int h,
    FormatTexture format, bool linear )
    : Texture( w, h, format, linear, GL_TEXTURE_2D )
  {
  }
  void Texture2D::apply( void ) // bool updateMipMaps = true
  {
    this->bind( );
    glTexImage2D(
      this->_target,
      0, // level
      _internalFormat,    // internalFormat
      this->getWidth( ),
      this->getHeight( ),
      0, // border
      _format, // format
      _type, // type
      _data
    );

    glTexParameteri( _target, GL_TEXTURE_WRAP_S,
      getWrapMode( ) == WrapMode::CLAMP_TO_EDGE ? GL_CLAMP_TO_EDGE : GL_REPEAT );
    glTexParameteri( _target, GL_TEXTURE_WRAP_T,
      getWrapMode( ) == WrapMode::CLAMP_TO_EDGE ? GL_CLAMP_TO_EDGE : GL_REPEAT );
    glTexParameteri( _target, GL_TEXTURE_MIN_FILTER,
      getMinFilter( ) == FilterMode::BILINEAR ? GL_LINEAR : GL_NEAREST );
    glTexParameteri( _target, GL_TEXTURE_MAG_FILTER,
      getMagFilter( ) == FilterMode::BILINEAR ? GL_LINEAR : GL_NEAREST );

    this->unbind( );
  }
  void Texture2D::loadImageTexture( const std::string& fileName )
  {
    std::string auxName = mb::FileSystem::getInstance()->getPathForResource( fileName );
    const char* fileName_ = auxName.c_str( );

    FreeImage_Initialise( TRUE );
    FREE_IMAGE_FORMAT format = FreeImage_GetFileType( fileName_, 0 );
    if ( format == FIF_UNKNOWN )
      format = FreeImage_GetFIFFromFilename( fileName_ );
    if ( ( format == FIF_UNKNOWN ) || !FreeImage_FIFSupportsReading( format ) )
      throw;
    FIBITMAP* img = FreeImage_Load( format, fileName_ );
    if ( img == nullptr )
      throw new mb::RuntimeException( "Image undefined" );
    FIBITMAP* tempImg = img;
    img = FreeImage_ConvertTo32Bits( img );
    FreeImage_Unload( tempImg );
    unsigned int width_ = FreeImage_GetWidth( img );
    unsigned int height_ = FreeImage_GetHeight( img );
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

    _width = width_;
    _height = height_;
    this->loadRawTexture( data );
  }

  mb::Texture2D* Texture2D::loadFromImage( const std::string& fileName )
  {
    mb::Texture2D* tex = new mb::Texture2D( );
    tex->loadImageTexture( fileName );
    tex->apply();
    return tex;
  }

  void Texture2D::bindToImageUnit( unsigned int unit, unsigned int access,
    unsigned int format, int level, bool layered, int layer )
  {
    glBindImageTexture( unit, _handler, level, layered, layer, access, format );
  }
}

namespace mb
{
  Texture2DArray::Texture2DArray( unsigned int w, unsigned int h,
    unsigned int d, FormatTexture format )
    : Texture2DArray( w, h, d, format, false )
  {
  }
  Texture2DArray::Texture2DArray( unsigned int w, unsigned int h,
    unsigned int d, FormatTexture format, bool linear )
    : Texture( w, h, format, linear, GL_TEXTURE_2D_ARRAY )
    , _depth( d )
  {
  }
  void Texture2DArray::apply( void ) // bool updateMipMaps = true
  {
    this->bind( );
    glTexParameteri( _target, GL_TEXTURE_WRAP_S,
      getWrapMode( ) == WrapMode::CLAMP_TO_EDGE ? GL_CLAMP_TO_EDGE : GL_REPEAT );
    glTexParameteri( _target, GL_TEXTURE_WRAP_T,
      getWrapMode( ) == WrapMode::CLAMP_TO_EDGE ? GL_CLAMP_TO_EDGE : GL_REPEAT );
    glTexParameteri( _target, GL_TEXTURE_WRAP_R,
      getWrapMode( ) == WrapMode::CLAMP_TO_EDGE ? GL_CLAMP_TO_EDGE : GL_REPEAT );
    glTexParameteri( _target, GL_TEXTURE_MIN_FILTER,
      getMinFilter( ) == FilterMode::BILINEAR ? GL_LINEAR : GL_NEAREST );
    glTexParameteri( _target, GL_TEXTURE_MAG_FILTER,
      getMagFilter( ) == FilterMode::BILINEAR ? GL_LINEAR : GL_NEAREST );

    /*
    TODO
    glTexImage3D(this->_target, this->_level, this->_internalFormat,
      width, height, data.size(), 0, this->_format, this->_type, nullptr);

    unsigned int i = 0;
    for (const auto& layer : data)
    {
      glTexSubImage3D(
        this->_target, 0, 0, 0, i, width, height, 1,
        this->_format, this->_type, layer
      );
      ++i;
    }*/

    this->unbind( );
  }
}

namespace mb
{
  Texture3D::Texture3D( unsigned int w, unsigned int h, unsigned int d,
    FormatTexture format )
    : Texture3D( w, h, d, format, false )
  {

  }
  Texture3D::Texture3D( unsigned int w, unsigned int h, unsigned int d,
    FormatTexture format, bool linear )
    : Texture( w, h, format, linear, GL_TEXTURE_3D )
    , _depth( d )
  {
  }
  void Texture3D::apply( void ) // bool updateMipMaps = true
  {
    this->bind( );
    glTexParameteri( _target, GL_TEXTURE_WRAP_S,
      getWrapMode( ) == WrapMode::CLAMP_TO_EDGE ? GL_CLAMP_TO_EDGE : GL_REPEAT );
    glTexParameteri( _target, GL_TEXTURE_WRAP_T,
      getWrapMode( ) == WrapMode::CLAMP_TO_EDGE ? GL_CLAMP_TO_EDGE : GL_REPEAT );
    glTexParameteri( _target, GL_TEXTURE_WRAP_R,
      getWrapMode( ) == WrapMode::CLAMP_TO_EDGE ? GL_CLAMP_TO_EDGE : GL_REPEAT );
    glTexParameteri( _target, GL_TEXTURE_MIN_FILTER,
      getMinFilter( ) == FilterMode::BILINEAR ? GL_LINEAR : GL_NEAREST );
    glTexParameteri( _target, GL_TEXTURE_MAG_FILTER,
      getMagFilter( ) == FilterMode::BILINEAR ? GL_LINEAR : GL_NEAREST );

    glTexImage3D(
      this->_target,
      0, // level
      _internalFormat,    // internalFormat
      this->getWidth( ),
      this->getHeight( ),
      this->getDepth( ),
      0, // border
      _format, // format
      _type, // type
      _data
    );

    this->unbind( );
  }
}
