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

#ifndef __MB_NORMALMATERIAL__
#define __MB_NORMALMATERIAL__

#include <mb/api.h>

#include "../Rendering/Material.hpp"
#include "../Rendering/Texture.hpp"
#include "../Maths/Color.hpp"
#include "../Maths/Vector4.hpp"

namespace mb
{
  class NormalMaterial : public Material
  {
  public:
    MB_API
      NormalMaterial( bool flat_shading = false, bool double_sided = false )
      : Material( )
    {
      this->addUniform( MB_PROJ_MATRIX,
        std::make_shared< mb::Matrix4Uniform >( ) );
      this->addUniform( MB_VIEW_MATRIX,
        std::make_shared< mb::Matrix4Uniform >( ) );
      this->addUniform( MB_MODEL_MATRIX,
        std::make_shared< mb::Matrix4Uniform >( ) );

      program = new mb::Program( );
      std::string headers_defines;
      headers_defines += ( flat_shading ? "#define FLAT_SHADING\n" : "" );
      headers_defines += ( double_sided ? "#define DOUBLE_SIDED\n" : "" );
      program->loadVertexShaderFromText(
      R"(#version 330 core)" + headers_defines + R"(
      uniform mat4 mb_MatrixM;
      uniform mat4 mb_MatrixV;
      uniform mat4 mb_MatrixP;

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
      mat3 normalMatrix = mat3( inverse( transpose( mb_MatrixV * mb_MatrixM ) ) );
      vec3 transformedNormal = normalMatrix * normal;
      vec3 position = vec3( attrPosition );
      vec4 mvPosition = mb_MatrixV * mb_MatrixM * vec4( position, 1.0 );
      outNormal = normalize( attrNormal );
      gl_Position = mb_MatrixP * mvPosition;
    })" );
      program->loadFragmentShaderFromText(
      R"(#version 330 core)" + headers_defines + R"(
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
  };
}

#endif /* __MB_NORMALMATERIAL__ */
