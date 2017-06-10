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

#ifndef __ERROR_MATERIAL__
#define __ERROR_MATERIAL__

#include <mb/mb.h>

class ErrorMaterial : public mb::Material
{
public:
  ErrorMaterial( void )
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

      uniform mat4 mb_MatrixM;
      uniform mat4 mb_MatrixV;
      uniform mat4 mb_MatrixP;

      void main()
      {
        gl_Position = mb_MatrixP * mb_MatrixV
          * mb_MatrixM * vec4(position, 1.0f);
      })" );
    program->loadFragmentShaderFromText( R"(
      #version 330 core
      out vec4 fragColor;

      void main( void )
      {
        fragColor = vec4(1.0, 0.5, 0.9, 1.0);
      })" );
    program->compileAndLink( );
    program->autocatching( );
  }
};

#endif /* __ERROR_MATERIAL__ */
