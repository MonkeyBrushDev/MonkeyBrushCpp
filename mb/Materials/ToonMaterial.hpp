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

      _levels = std::make_shared< mb::FloatUniform >( 5.0f );

      this->addUniform( levelsUnifName, _levels );

      program = new mb::Program( );
      program->loadVertexShaderFromText( R"(
        #version 330 core
        layout (location = 0) in vec3 position;
        layout (location = 1) in vec3 normal;

        out vec3 outPosition;
        out vec3 Normal;

        uniform mat4 mb_MatrixM;
        uniform mat4 mb_MatrixV;
        uniform mat4 mb_MatrixP;

        void main()
        {
          gl_Position = mb_MatrixP * mb_MatrixV * mb_MatrixM * vec4(position, 1.0f);
          mat3 normalMatrix = mat3(transpose(inverse( mb_MatrixM )));
          Normal = normalMatrix * normal;
          outPosition = vec3( mb_MatrixM * vec4( position, 1.0 ) );
        })" );
      program->loadFragmentShaderFromText( R"(
        #version 330 core

        in vec3 outPosition;
        in vec3 Normal;

        out vec4 fragColor;

        uniform vec4 DiffuseColor;

        uniform mat4 mb_MatrixV;

        uniform float levels;

        void main()
        {
          vec3 viewPos = -transpose(mat3(mb_MatrixV)) * mb_MatrixV[3].xyz;
          float scaleFactor = 1.0 / levels;
          vec3 n = normalize(Normal);
          vec3 s = normalize(viewPos.xyz - outPosition.xyz);
          float cosine = dot(s, n);
          vec3 diffuse = DiffuseColor.rgb * floor(cosine * levels) * scaleFactor;
          fragColor = vec4( diffuse, 1.0 );
        })" );
      program->compileAndLink( );
      program->autocatching( );
    }
    MB_API
    void setLevels( const float &v )
    {
      _levels->value( v );
    }
  protected:
    mb::UniformPtr _levels;
  private:
    const char* levelsUnifName = "levels";
  };
}

#endif /* __MB_TOONMATERIAL__ */
