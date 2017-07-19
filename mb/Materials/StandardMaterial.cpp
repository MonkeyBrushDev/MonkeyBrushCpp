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

#include "StandardMaterial.hpp"

namespace mb
{
  StandardMaterial::StandardMaterial( void )
    : Material( )
  {
    this->addStandardUniforms( );

    _colorMap = std::make_shared< mb::TextureUniform >( );
    _normalMap = std::make_shared< mb::TextureUniform >( );
    _diffuse = std::make_shared< mb::Vector4Uniform >( mb::Vector4( 1.0f ) );
    _specularMap = std::make_shared< mb::TextureUniform >( );
    _shininess = std::make_shared< mb::FloatUniform >( 64.0f );
    _normalScale = std::make_shared< mb::FloatUniform >( 0.5f );

    this->addUniform( "DiffuseTexture", _colorMap );
    this->addUniform( "DiffuseColor", _diffuse );
    this->addUniform( "ShininessValue", _shininess );
    this->addUniform( "SpecularTexture", _specularMap );
    this->addUniform( "NormalTexture", _normalMap );
    this->addUniform( "NormalScale", _normalScale );

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

      uniform sampler2D DiffuseTexture;
      uniform sampler2D NormalTexture;
      //uniform sampler2D SpecularTexture;
      uniform vec4 DiffuseColor;

      uniform mat4 view;

      uniform float NormalScale;
      uniform float ShininessValue;

      #import<normal_mapping.glsl>(normalCustomTexture=NormalTexture,normalScale=NormalScale)

      void main()
      {
        vec3 lightPosition = vec3(view * vec4(2.0, 15.0, 15.0, 1.0));
        vec3 viewPos = -transpose(mat3(view)) * view[3].xyz;

        vec3 ambient = vec3(0.4);

        vec3 norm = normalize(Normal);
        norm = perturb_normal(-outPosition, norm);

        vec3 lightDir = normalize(lightPosition - outPosition);
        float diff = max(dot(norm, lightDir), 0.0);
        //vec3 diffuse = texture( DiffuseTexture, TexCoord ).rgb * diff;
        vec3 diffuse = vec3(1.0) * diff;

        vec3 viewDir = normalize(viewPos - outPosition);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), ShininessValue);
        vec3 specular = vec3(spec);

        //fragColor = vec4((ambient + diffuse + specular) * DiffuseColor.rgb, 1.0);
        fragColor = vec4((ambient + diffuse + specular) * texture( DiffuseTexture, TexCoord ).rgb, 1.0);

        fragColor *= DiffuseColor;

        /*fragColor = vec4( TexCoord, 0.0, 1.0 );
        fragColor = texture( DiffuseTexture, TexCoord );
        fragColor *= DiffuseColor;
        //fragColor.rgb = Normal;

        if (gl_FragCoord.x < 250)
        {
          fragColor.rgb = norm;
        }
        fragColor.rgb = viewPos;*/
      })" );
    program->compileAndLink( );
    program->autocatching( );
  }
  void StandardMaterial::setColor( const mb::Color &color )
  {
    _diffuse->value( mb::Color( color.r( ), color.g( ), color.b( ), color.a( ) ) );
  }
  void StandardMaterial::setShininess( const float &v )
  {
    _shininess->value( v );
  }
  void StandardMaterial::setNormalScale( const float &v )
  {
    _normalScale->value( v );
  }
  void StandardMaterial::setColorMap( mb::Texture2D *texture )
  {
    _colorMap->value( texture );
  }
  void StandardMaterial::setSpecularMap( mb::Texture2D *texture )
  {
    _specularMap->value( texture );
  }
  void StandardMaterial::setNormalMap( mb::Texture2D *texture )
  {
    _normalMap->value( texture );
  }
}
