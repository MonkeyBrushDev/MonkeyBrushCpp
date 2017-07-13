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

#include "ToonMaterial.hpp"

namespace mb
{
  ToonMaterial::ToonMaterial( void )
  : Material( )
  {
    this->addStandardUniforms( );

    _levels = std::make_shared< mb::FloatUniform >( 5.0f );

    this->addUniform( "levels", _levels );

    program = std::make_shared< mb::Program >( );
    program->loadVertexShaderFromText( R"(
      #version 330 core
      layout (location = 0) in vec3 position;
      layout (location = 1) in vec3 normal;

      out vec3 outPosition;
      out vec3 Normal;

      uniform mat4 MB_MATRIXM;
      uniform mat4 MB_MATRIXV;
      uniform mat4 MB_MATRIXP;

      void main()
      {
        gl_Position = MB_MATRIXP * MB_MATRIXV * MB_MATRIXM * vec4(position, 1.0f);
        mat3 normalMatrix = mat3(transpose(inverse( MB_MATRIXM )));
        Normal = normalMatrix * normal;
        outPosition = vec3( MB_MATRIXM * vec4( position, 1.0 ) );
      })" );
    program->loadFragmentShaderFromText( R"(
      #version 330 core

      in vec3 outPosition;
      in vec3 Normal;

      out vec4 fragColor;

      uniform vec4 DiffuseColor;

      uniform mat4 MB_MATRIXV;

      uniform float levels;

      void main()
      {
        vec3 viewPos = -transpose(mat3(MB_MATRIXV)) * MB_MATRIXV[3].xyz;
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
  void ToonMaterial::setLevels( const float &v )
  {
    _levels->value( v );
  }
}
