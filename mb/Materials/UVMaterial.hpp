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

#ifndef __MB_UVMATERIAL__
#define __MB_UVMATERIAL__

#include <mb/api.h>

#include "../Rendering/Material.hpp"
#include "../Rendering/Texture.hpp"
#include "../Maths/Color.hpp"
#include "../Maths/Vector4.hpp"

namespace mb
{
  class UVMaterial: public Material
  {
  public:
    MB_API
    UVMaterial( void )
    : Material( )
    {
      this->addUniform( MB_PROJ_MATRIX,
        std::make_shared< mb::Matrix4Uniform >( ) );
      this->addUniform( MB_VIEW_MATRIX,
        std::make_shared< mb::Matrix4Uniform >( ) );
      this->addUniform( MB_MODEL_MATRIX,
        std::make_shared< mb::Matrix4Uniform >( ) );

      program = new mb::Program( );
      program->loadVertexShaderFromText( R"(
        #version 330 core
        layout (location = 0) in vec3 position;
        //layout (location = 1) in vec3 normal;
        layout (location = 2) in vec2 texCoord;

        out vec2 TexCoord;

        uniform mat4 mb_MatrixM;
        uniform mat4 mb_MatrixV;
        uniform mat4 mb_MatrixP;

        void main()
        {
          gl_Position = mb_MatrixP * mb_MatrixV * mb_MatrixM * vec4(position, 1.0f);
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
  };
}

#endif /* __MB_UVMATERIAL__ */
