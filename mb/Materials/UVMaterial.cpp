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

#include "UVMaterial.hpp"
namespace mb
{
  UVMaterial::UVMaterial( void )
    : Material( )
  {
    this->addStandardUniforms( );

    program = new mb::Program( );
    program->loadVertexShaderFromText( R"(
      #version 330 core
      layout (location = 0) in vec3 position;
      //layout (location = 1) in vec3 normal;
      layout (location = 2) in vec2 texCoord;

      out vec2 TexCoord;

      uniform mat4 MB_MATRIXM;
      uniform mat4 MB_MATRIXV;
      uniform mat4 MB_MATRIXP;

      void main()
      {
        gl_Position = MB_MATRIXP * MB_MATRIXV * MB_MATRIXM * vec4(position, 1.0f);
        TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);
      })" );
    program->loadFragmentShaderFromText( R"(
      #version 330 core

      in vec2 TexCoord;

      out vec4 fragColor;

      void main( )
      {
        fragColor = vec4( TexCoord.xy, 0.0, 1.0 );
      })" );
    program->compileAndLink( );
    program->autocatching( );
  }
}
