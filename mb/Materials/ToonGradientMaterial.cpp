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

#include "ToonGradientMaterial.hpp"

namespace mb
{
  ToonGradientMaterial::ToonGradientMaterial( void )
  : Material( )
  {
    this->addStandardUniforms( );

    _gradientMap = std::make_shared< mb::TextureUniform >( );
    _diffuse = std::make_shared< mb::Vector4Uniform >( mb::Vector4( 1.0f ) );
    _shininess = std::make_shared< mb::FloatUniform >( 64.0f );

    this->addUniform( "GradientTexture", _gradientMap );
    this->addUniform( "DiffuseColor", _diffuse );
    this->addUniform( "ShininessValue", _shininess );

    program = new mb::Program( );
    program->loadVertexShaderFromText( R"(
      #version 330 core
      layout (location = 0) in vec3 position;
      layout (location = 1) in vec3 normal;
      layout (location = 2) in vec2 texCoord;

      out vec3 outPosition;
      out vec3 Normal;
      out vec2 TexCoord;

      uniform mat4 MB_MATRIXM;
      uniform mat4 MB_MATRIXV;
      uniform mat4 MB_MATRIXP;

      void main()
      {
        gl_Position = MB_MATRIXP * MB_MATRIXV * MB_MATRIXM * vec4(position, 1.0f);
        TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);
        mat3 normalMatrix = mat3(transpose(inverse( MB_MATRIXM )));
        Normal = normalMatrix * normal;
        outPosition = vec3( MB_MATRIXM * vec4( position, 1.0 ) );
      })" );
    program->loadFragmentShaderFromText( R"(
      #version 330 core

      in vec3 outPosition;
      in vec3 Normal;
      in vec2 TexCoord;

      out vec4 fragColor;

      uniform sampler2D GradientTexture;
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
        vec3 diffuse = vec3(1.0) * diff;

        vec3 viewDir = normalize(viewPos - outPosition);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), ShininessValue);
        vec3 specular = vec3(spec);

        fragColor = vec4((ambient + diffuse + specular), 1.0 );

        float dotNL = dot( norm, lightDir );
        vec2 coord = vec2( dotNL * 0.5 + 0.5, 0.0 );

        float NdotL = dot(Normal, lightDir);
        NdotL = texture(GradientTexture, vec2(NdotL, 0.5)).r;

        fragColor *= vec4(vec3(NdotL), 1.0);

        fragColor *= DiffuseColor;
      })" );
    program->compileAndLink( );
    program->autocatching( );
  }
  void ToonGradientMaterial::setColor( const mb::Color &color )
  {
    _diffuse->value( mb::Color( color.r( ), color.g( ), color.b( ), color.a( ) ) );
  }
  void ToonGradientMaterial::setShininess( const float &v )
  {
    _shininess->value( v );
  }
  void ToonGradientMaterial::setGradientMap( mb::Texture2D *texture )
  {
    _gradientMap->value( texture );
  }
}
