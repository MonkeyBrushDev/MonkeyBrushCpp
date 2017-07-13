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

#ifndef __MB_FONTMATERIAL__
#define __MB_FONTMATERIAL__

#include <mb/api.h>

#include "../Rendering/Material.hpp"
#include "../Rendering/Texture.hpp"
#include "../Maths/Color.hpp"
#include "../Maths/Vector4.hpp"

namespace mb
{
  class FontMaterial: public Material
  {
  public:
    MB_API
    FontMaterial( void )
    : Material( )
    {
      this->addUniform( "projection",
        std::make_shared< mb::Matrix4Uniform >( ) );
      this->addUniform( "view",
        std::make_shared< mb::Matrix4Uniform >( ) );
      this->addUniform( "model",
        std::make_shared< mb::Matrix4Uniform >( ) );

      _colorMap = std::make_shared< mb::TextureUniform >( );
      _diffuse = std::make_shared< mb::Vector4Uniform >( mb::Vector4( 1.0f ) );

      this->addUniform( "DiffuseTexture", _colorMap );
      this->addUniform( "DiffuseColor", _diffuse );

      program = std::make_shared< mb::Program >( );
      program->loadVertexShaderFromText( R"(
        #version 330 core
        layout (location = 0) in vec3 position;
        layout (location = 1) in vec3 texCoord;

        out vec2 outTexCoord;

        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;

        void main()
        {
          outTexCoord = texCoord;
          gl_Position = projection * view * model * vec4(position, 1.0f);
        })" );
      program->loadFragmentShaderFromText( R"(
        #version 330 core

        in vec2 outTexCoord;
        uniform sampler2D DiffuseTexture;
        uniform vec4 DiffuseColor;

        void main( )
        {
          fragColor = DiffuseColor>
          float c = texture2D( DiffuseTexture, outTexCoord ).r;
          fragColor *= vec4( c );
          if ( fragColor.a < 0.1 ) discard;
        })" );
      program->compileAndLink( );
      program->autocatching( );
    }
    MB_API
    void setColor( const Color &color )
    {
      _diffuse->value( mb::Color( color.r( ), color.g( ), color.b( ), color.a( ) ) );
    }
    MB_API
    void setColorMap( mb::Texture2D *texture )
    {
      _colorMap->value( texture );
    }
  protected:
    mb::UniformPtr _diffuse;
    mb::UniformPtr _colorMap;
  };
}

#endif /* __MB_FONTMATERIAL__ */
