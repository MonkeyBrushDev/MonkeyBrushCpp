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

#ifndef __MB_COLORMATERIAL__
#define __MB_COLORMATERIAL__

#include <mb/api.h>

#include "Material.hpp"
#include "../Rendering/Texture.hpp"
#include "../Maths/Color.hpp"
#include "../Maths/Vector4.hpp"

namespace mb
{
  class ColorMaterial: public Material
  {
  public:
    MB_API
    ColorMaterial( void )
    : Material( )
    {
      this->addUniform( "projection",
        std::make_shared< mb::Uniform >( mb::UniformType::Matrix4 ) );
      this->addUniform( "view",
        std::make_shared< mb::Uniform >( mb::UniformType::Matrix4 ) );
      this->addUniform( "model",
        std::make_shared< mb::Uniform >( mb::UniformType::Matrix4 ) );

      _colorMap = std::make_shared< mb::Uniform >( mb::UniformType::TextureSampler );
      _diffuse = std::make_shared< mb::Uniform >( mb::UniformType::Vector4, Vector4( 1.0f ) );
      _shininess = std::make_shared< mb::Uniform >( mb::UniformType::Float, 64.0f );

      this->addUniform( colorMapUnifName, _colorMap );
      this->addUniform( colorUnifName, _diffuse );
      this->addUniform( shininessUnifName, _shininess );

      program = new mb::Program( );
      program->loadVertexShaderFromText( R"(
        #version 330 core
        layout (location = 0) in vec3 position;
        layout (location = 0) in vec3 normal;
        layout (location = 2) in vec2 texCoord;

        out vec3 outPosition;
        out vec3 Normal;
        out vec2 TexCoord;

        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;

        void main()
        {
          gl_Position = projection * view * model * vec4(position, 1.0f);
          TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);
          mat3 normalMatrix = mat3(transpose(inverse( model )));
          Normal = normalMatrix * normal;
          outPosition = vec3( model * vec4( position, 1.0 ) );
        })" );
      program->loadFragmentShaderFromText( R"(
        #version 330 core

        in vec3 outPosition;
        in vec3 Normal;
        in vec2 TexCoord;

        out vec4 fragColor;

        uniform sampler2D DiffuseTexture;
        uniform vec4 DiffuseColor;

        uniform mat4 view;

        uniform float ShininessValue;

        void main()
        {
          vec3 lightPosition = vec3(view * vec4(2.0, 15.0, 15.0, 1.0));
          vec3 viewPos = -transpose(mat3(view)) * view[3].xyz;

          vec3 ambient = vec3(0.4);

          vec3 norm = normalize(Normal);

          vec3 lightDir = normalize(lightPosition - outPosition);
          float diff = max(dot(norm, lightDir), 0.0);
          //vec3 diffuse = texture( DiffuseTexture, TexCoord ).rgb * diff;
          vec3 diffuse = vec3(1.0) * diff;

          vec3 viewDir = normalize(viewPos - outPosition);
          vec3 reflectDir = reflect(-lightDir, norm);
          float spec = pow(max(dot(viewDir, reflectDir), 0.0), ShininessValue);
          vec3 specular = vec3(spec);

          fragColor = vec4((ambient + diffuse + specular) * texture( DiffuseTexture, TexCoord ).rgb, 1.0);

          fragColor *= DiffuseColor;
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
    void setShininess( const float &v )
    {
      _shininess->value( v );
    }
    MB_API
    void setColorMap( mb::Texture2D *texture )
    {
      _colorMap->value( texture );
    }
  protected:
    mb::UniformPtr _diffuse;
    mb::UniformPtr _shininess;
    mb::UniformPtr _colorMap;
  private:
    const char* colorMapUnifName = "DiffuseTexture";
    const char* colorUnifName = "DiffuseColor";
    const char* shininessUnifName = "ShininessValue";
  };
}

#endif /* __MB_COLORMATERIAL__ */
