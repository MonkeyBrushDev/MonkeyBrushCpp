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

#ifndef __MB_TOONMATERIAL__
#define __MB_TOONMATERIAL__

#include <mb/api.h>

#include "../Rendering/Material.hpp"
#include "../Rendering/Texture.hpp"
#include "../Maths/Color.hpp"
#include "../Maths/Vector4.hpp"

namespace mb
{
  class ToonMaterial: public Material
  {
  public:
    MB_API
    ToonMaterial( void )
    : Material( )
    {
      this->addUniform( MB_PROJ_MATRIX,
        std::make_shared< mb::Matrix4Uniform >( ) );
      this->addUniform( MB_VIEW_MATRIX,
        std::make_shared< mb::Matrix4Uniform >( ) );
      this->addUniform( MB_MODEL_MATRIX,
        std::make_shared< mb::Matrix4Uniform >( ) );

      _diffuse = std::make_shared< mb::Vector4Uniform >( mb::Vector4( 1.0f ) );
      _shininess = std::make_shared< mb::FloatUniform >( 64.0f );

      this->addUniform( colorUnifName, _diffuse );
      this->addUniform( shininessUnifName, _shininess );

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

        uniform vec4 DiffuseColor;

        uniform mat4 mb_MatrixV;

        uniform float ShininessValue;


        /*uniform*/ float levels = 5.0;


        void main()
        {
          /*vec3 lightPosition = vec3(mb_MatrixV * vec4(2.0, 15.0, 15.0, 1.0));
          vec3 viewPos = -transpose(mat3(mb_MatrixV)) * mb_MatrixV[3].xyz;

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

          fragColor = vec4( 0.0, 0.0, 0.0, 1.0 );

          float cosine = max( 0.0, dot( lightDir, Normal ) );

          fragColor *= vec4(vec3(floor( cosine * levels ) * scaleFactor), 1.0);

          fragColor = DiffuseColor;*/

          vec3 viewPos = -transpose(mat3(mb_MatrixV)) * mb_MatrixV[3].xyz;
          float scaleFactor = 1.0 / levels;
          vec3 n = normalize(Normal);
          vec3 s = normalize(viewPos.xyz - outPosition.xyz);
          float cosine = dot(s, n);
          vec3 diffuse = DiffuseColor.rgb * floor(cosine * levels) * scaleFactor;
          fragColor = vec4(diffuse, 1.0);
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
  protected:
    mb::UniformPtr _diffuse;
    mb::UniformPtr _shininess;
  private:
    const char* colorUnifName = "DiffuseColor";
    const char* shininessUnifName = "ShininessValue";
  };
}

#endif /* __MB_TOONMATERIAL__ */
