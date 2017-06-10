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

#include "../Rendering/Material.hpp"
#include "../Rendering/Texture.hpp"
#include "../Maths/Color.hpp"
#include "../Maths/Vector4.hpp"

namespace mb
{
  class StandardMaterial: public Material
  {
  public:
    MB_API
    StandardMaterial( void )
    : Material( )
    {
      this->addUniform( MB_PROJ_MATRIX,
        std::make_shared< mb::Matrix4Uniform >( ) );
      this->addUniform( MB_VIEW_MATRIX,
        std::make_shared< mb::Matrix4Uniform >( ) );
      this->addUniform( MB_MODEL_MATRIX,
        std::make_shared< mb::Matrix4Uniform >( ) );

      _colorMap = std::make_shared< mb::TextureUniform >( );
      _normalMap = std::make_shared< mb::TextureUniform >( );
      _diffuse = std::make_shared< mb::Vector4Uniform >( mb::Vector4( 1.0f ) );
      _specularMap = std::make_shared< mb::TextureUniform >( );
      _shininess = std::make_shared< mb::FloatUniform >( 64.0f );
      _normalScale = std::make_shared< mb::FloatUniform >( 0.5f );

      this->addUniform( colorMapUnifName, _colorMap );
      this->addUniform( colorUnifName, _diffuse );
      this->addUniform( shininessUnifName, _shininess );
      this->addUniform( specularMapUnifName, _specularMap );
      this->addUniform( normalMapUnifName, _normalMap );
      this->addUniform( normalScaleUnifName, _normalScale );

      program = new mb::Program( );
      program->loadVertexShaderFromText( R"(
        #version 330 core
        layout (location = 0) in vec3 position;
        layout (location = 1) in vec3 normal;
        layout (location = 2) in vec2 texCoord;

        out vec3 outPosition;
        out vec3 Normal;
        out vec2 TexCoord;

        uniform mat4 mb_MatrixM;
        uniform mat4 mb_MatrixV;
        uniform mat4 mb_MatrixP;

        void main()
        {
          gl_Position = mb_MatrixP * mb_MatrixV * mb_MatrixM * vec4(position, 1.0f);
          TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);
          mat3 normalMatrix = mat3(transpose(inverse( mb_MatrixM )));
          Normal = normalMatrix * normal;
          outPosition = vec3( mb_MatrixM * vec4( position, 1.0 ) );
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
    void setNormalScale( const float &v )
    {
      _normalScale->value( v );
    }
    MB_API
    void setColorMap( mb::Texture2D *texture )
    {
      _colorMap->value( texture );
    }
    MB_API
    void setSpecularMap( mb::Texture2D *texture )
    {
      _specularMap->value( texture );
    }
    MB_API
    void setNormalMap( mb::Texture2D *texture )
    {
      _normalMap->value( texture );
    }
  protected:
    mb::UniformPtr _diffuse;
    mb::UniformPtr _shininess;
    mb::UniformPtr _colorMap;
    mb::UniformPtr _normalMap;
    mb::UniformPtr _normalScale;
    mb::UniformPtr _specularMap;

  private:
    const char* colorMapUnifName = "DiffuseTexture";
    const char* colorUnifName = "DiffuseColor";
    const char* shininessUnifName = "ShininessValue";
    const char* normalMapUnifName = "NormalTexture";
    const char* specularMapUnifName = "SpecularTexture";
    const char* normalScaleUnifName = "NormalScale";
  };
}

#endif /* __MB_STANDARDMATERIAL__ */
