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

#ifndef __MB_POINTMATERIAL__
#define __MB_POINTMATERIAL__

#include <mb/api.h>

#include "../Rendering/Material.hpp"
#include "../Rendering/Texture.hpp"
#include "../Maths/Color.hpp"
#include "../Maths/Vector4.hpp"

namespace mb
{
  class PointMaterial : public Material
  {
  public:
    MB_API
      PointMaterial( bool size_attenuation = false )
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
      headers_defines += ( size_attenuation ? "#define SIZE_ATTENUATION\n" : "" );
      program->loadVertexShaderFromText(
      R"(#version 330 core)" + headers_defines + R"(

      uniform mat4 mb_MatrixM;
      uniform mat4 mb_MatrixV;
      uniform mat4 mb_MatrixP;

      in vec3 attrPosition;

      const float size = 10.0;
      const float scale = 64.0;

      void main( )
      {
        vec3 position = vec3( attrPosition );

        vec4 mvPosition = mb_MatrixV * mb_MatrixM * vec4( position, 1.0 );

      #ifdef SIZE_ATTENUATION
        gl_PointSize = size * ( scale / mvPosition.z );
      #else
        gl_PointSize = size;
      #endif

        gl_Position = mb_MatrixP * mvPosition;
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
  private:
    const char* colorUnifName = "DiffuseColor";
  };
}

#endif /* __MB_POINTMATERIAL__ */
