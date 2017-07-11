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

#include "PointMaterial.hpp"
namespace mb
{
  PointMaterial::PointMaterial( bool size_attenuation )
    : Material( )
  {
    this->addStandardUniforms( );

    program = new mb::Program( );
    std::string headers_defines;
    headers_defines += ( size_attenuation ? "#define SIZE_ATTENUATION\n" : "" );
    program->loadVertexShaderFromText(
    R"(#version 330 core)" + headers_defines + R"(

    uniform mat4 MB_MATRIXM;
    uniform mat4 MB_MATRIXV;
    uniform mat4 MB_MATRIXP;

    in vec3 attrPosition;

    const float size = 10.0;
    const float scale = 64.0;

    void main( )
    {
      vec3 position = vec3( attrPosition );

      vec4 mvPosition = MB_MATRIXV * MB_MATRIXM * vec4( position, 1.0 );

    #ifdef SIZE_ATTENUATION
      gl_PointSize = size * ( scale / mvPosition.z );
    #else
      gl_PointSize = size;
    #endif

      gl_Position = MB_MATRIXP * mvPosition;
    })" );
    program->loadFragmentShaderFromText(
    R"(#version 330 core
    uniform vec4 DiffuseColor;

    out vec4 fragColor;

    void main( )
    {
      fragColor = DiffuseColor;
    })" );
    program->compileAndLink( );
    program->autocatching( );
  }
}
