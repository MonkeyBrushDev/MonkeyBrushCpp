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

#include "NormalMaterial.hpp"
namespace mb
{
  NormalMaterial::NormalMaterial( bool flat_shading, bool double_sided )
    : Material( )
  {
    this->addStandardUniforms( );

    std::string headers_defines;
    headers_defines += ( flat_shading ? "#define FLAT_SHADING\n" : "" );
    headers_defines += ( double_sided ? "#define DOUBLE_SIDED\n" : "" );
    program->loadVertexShaderFromText(
    R"(#version 330 core
      )" + headers_defines + R"(
      uniform mat4 MB_MATRIXM;
      uniform mat4 MB_MATRIXV;
      uniform mat4 MB_MATRIXP;

      in vec3 attrPosition;
      in vec3 attrNormal;
      #if defined( FLAT_SHADING )
        flat out vec3 outNormal;
      #else
        out vec3 outNormal;
      #endif

      void main( void )
      {
        vec3 normal = vec3( attrNormal );
      #ifdef FLIP_SIDED
        normal = -normal;
      #endif
      mat3 normalMatrix = mat3( inverse( transpose( MB_MATRIXV * MB_MATRIXM ) ) );
      vec3 transformedNormal = normalMatrix * normal;
      vec3 position = vec3( attrPosition );
      vec4 mvPosition = MB_MATRIXV * MB_MATRIXM * vec4( position, 1.0 );
      outNormal = normalize( attrNormal );
      gl_Position = MB_MATRIXP * mvPosition;
    })" );
    program->loadFragmentShaderFromText(
    R"(#version 330 core
    )" + headers_defines + R"(
    #if defined( FLAT_SHADING )
      flat in vec3 outNormal;
    #else
      in vec3 outNormal;
    #endif

    uniform float alpha; // 1.0

    vec3 packNormalToRGB( const in vec3 normal )
    {
      return normalize( normal ) * 0.5 + 0.5;
    }

    out vec4 fragColor;

    void main( )
    {
      vec3 normal = outNormal;
      #import<normal_flip.glsl>
      fragColor = vec4 (packNormalToRGB(normal), alpha);
    })" );
    program->compileAndLink( );
    program->autocatching( );
  }
}
