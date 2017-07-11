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

#include "PostProcessMaterial.hpp"
namespace mb
{
  PostProcessMaterial::PostProcessMaterial( void )
    : PostProcessMaterial(
    R"(#version 330
    uniform vec3 color;
    out vec4 fragColor;
    in vec2 uv;
    void main( void )
    {
      fragColor = vec4( uv, 0.0, 1.0 );
    })")
  {
  }
  PostProcessMaterial::PostProcessMaterial( const std::string& fragmentSource )
    : Material( )
  {
    program = new mb::Program( );
    program->loadVertexShaderFromText( R"(
      #version 330
      layout( location = 0 ) in vec3 vertPosition;
      out vec2 uv;
      void main( void )
      {
        uv = vec2( vertPosition.xy * 0.5 ) + vec2( 0.5 );
        gl_Position = vec4( vertPosition, 1.0 );
      })" );
    program->loadFragmentShaderFromText( fragmentSource );
    program->compileAndLink( );
    program->autocatching( );
  }
}
