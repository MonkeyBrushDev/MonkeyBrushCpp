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

#ifndef __XRAY_MATERIAL__
#define __XRAY_MATERIAL__

#include <mb/mb.h>

class XRayMaterial : public mb::Material
{
public:
  XRayMaterial( void )
  : Material( )
  {
    this->addStandardUniforms( );

    program = new mb::Program( );
    program->loadVertexShaderFromText( R"(
      #version 330 core
      layout (location = 0) in vec3 position;
      layout (location = 1) in vec3 normal;

      out vec3 outPosition;
      out vec3 outNormal;

      uniform mat4 MB_MATRIXM;
      uniform mat4 MB_MATRIXV;
      uniform mat4 MB_MATRIXP;

      void main()
      {
        gl_Position = MB_MATRIXP * MB_MATRIXV * MB_MATRIXM * vec4(position, 1.0);
        outPosition = vec3(MB_MATRIXV * MB_MATRIXM * vec4(position, 1.0));
        mat3 normalMatrix = mat3(transpose(inverse(MB_MATRIXV * MB_MATRIXM )));
        outNormal = normalMatrix * normal;
      })" );
    program->loadFragmentShaderFromText( R"(
      #version 330 core
      in vec3 outPosition;
      in vec3 outNormal;

      out vec4 fragColor;

      void main( void )
      {
        float edgefalloff = 0.01;
        float opac = dot( normalize( -outNormal ), normalize( -outPosition ));
        opac = abs( opac );
        opac = 1.0 - pow( opac, edgefalloff );
        fragColor = opac * Cs;
        fragColor.a = opac;
      })" );
    program->compileAndLink( );
    program->autocatching( );
  }
};

#endif /* __XRAY_MATERIAL__ */
