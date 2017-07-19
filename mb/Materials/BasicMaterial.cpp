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

#include "BasicMaterial.hpp"
#include "../Maths/Vector4.hpp"

namespace mb
{
  BasicMaterial::BasicMaterial( void )
    : Material( )
  {
    this->addStandardUniforms( );

    _diffuse = std::make_shared< mb::Vector4Uniform >( mb::Vector4( 1.0f ) );

    this->addUniform( "DiffuseColor", _diffuse );

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
        outPosition = vec3( MB_MATRIXM * vec4( position, 1.0 ) );
        Normal = normal;
      })" );
    program->loadFragmentShaderFromText( R"(
      #version 330 core

      in vec3 outPosition;
      in vec3 Normal;

      out vec4 fragColor;

      uniform vec4 DiffuseColor;
      uniform mat4 view;

      void main()
      {
        vec3 viewPos = -transpose(mat3(view)) * view[3].xyz;
        vec3 L = normalize(viewPos - outPosition);
        vec3 N = normalize( Normal );
        float dif = dot( N, L );
        dif = clamp( dif, 0.0, 1.0 );
        fragColor = vec4( DiffuseColor.rgb * ( dif + 0.3 ), DiffuseColor.a );
      })" );
    program->compileAndLink( );
    program->autocatching( );
  }
  void BasicMaterial::setColor( const mb::Color &color )
  {
    _diffuse->value( mb::Color( color.r( ), color.g( ), color.b( ), color.a( ) ) );
  }
}
