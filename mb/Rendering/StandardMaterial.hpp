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

#ifndef __MB_STANDARDMATERIAL__
#define __MB_STANDARDMATERIAL__

#include <mb/api.h>

#include "Material.hpp"
#include "Texture.hpp"

namespace mb
{
  class Color4
  {
  public:
    Color4( float r_, float g_, float b_, float a_ )
      : r( r_ ) , g( g_ ) , b( b_ ) , a( a_ )
    {
    }
    float r;
    float g;
    float b;
    float a;
  };
  class StandardMaterial: public Material
  {
  public:
    MB_API
    StandardMaterial( void )
      : _diffuse( 1.0f, 1.0f, 1.0f, 1.0f )
      , _shininess( 32.0f )
      , _colorMap( nullptr )
      , _specularMap( nullptr )
      , _normalMap( nullptr )
    {
    }
    MB_API
    const Color4 &getColor( void ) const
    {
      return _diffuse;
    }
    MB_API
    void setColor( const Color4 &color )
    {
      _diffuse = color;
    }
    MB_API
    const float &getShininess( void ) const
    {
      return _shininess;
    }
    MB_API
    void setShininess( const float &v )
    {
      _shininess = v;
    }
    MB_API
    Texture* getColorMap( void )
    {
      return _colorMap;
    }
    MB_API
    void setColorMap( Texture *texture )
    {
      _colorMap = texture;
    }
    MB_API
    Texture* getSpecularMap( void )
    {
      return _specularMap;
    }
    MB_API
    void setSpecularMap( Texture *texture )
    {
      _specularMap = texture;
    }
    MB_API
    Texture* getNormalMap( void )
    {
      return _normalMap;
    }
    MB_API
    void setNormalMap( Texture *texture )
    {
      _normalMap = texture;
    }
  protected:
    Color4 _diffuse;
    float _shininess;
    Texture* _colorMap;
    Texture* _specularMap;
    Texture* _normalMap;
  };
}

#endif /* __MB_STANDARDMATERIAL__ */
