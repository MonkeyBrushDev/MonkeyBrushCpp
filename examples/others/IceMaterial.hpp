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

#ifndef __ICE_MATERIAL__
#define __ICE_MATERIAL__

#include <mb/mb.h>

class IceMaterial : public mb::Material
{
public:
  IceMaterial( void )
  : Material( )
  {
    this->addStandardUniforms( );

    this->addUniform( "DiffuseColor",
      std::make_shared mb::Vector4Uniform >( ) );

    customMaterial->state().blending().setEnabled(true);

    program = new mb::Program( );
    program->loadVertexShaderFromText( R"(
      #version 330 core
      layout (location = 0) in vec3 position;
      layout (location = 1) in vec3 normal;

      out vec3 outPosition;
      out vec3 worldNormal;

      uniform mat4 MB_MATRIXM;
      uniform mat4 MB_MATRIXV;
      uniform mat4 MB_MATRIXP;

      void main()
      {
        gl_Position = MB_MATRIXP * MB_MATRIXV * MB_MATRIXM * vec4(position, 1.0);
        outPosition = vec3(MB_MATRIXM * vec4(position, 1.0));
        mat3 normalMatrix = mat3(transpose(inverse( MB_MATRIXM )));
        worldNormal = normalMatrix * normal;
      })" );
    program->loadFragmentShaderFromText( R"(
      #version 330 core
      in vec3 outPosition;
      in vec3 worldNormal;

      out vec4 fragColor;

      uniform mat4 MB_MATRIXV;

      uniform vec4 DiffuseColor;
      /*uniform */float _DotProduct = 0.25; // [-1.0, 1.0];

      void main( void )
      {
        vec3 viewPos = -transpose(mat3(MB_MATRIXV)) * MB_MATRIXV[3].xyz;

        vec3 viewDir = normalize( viewPos - outPosition );

        fragColor.rgb = DiffuseColor.rgb;
        float border = 1.0 - (abs(dot(viewDir, worldNormal)));
        float alpha = (border * (1.0 - _DotProduct) + _DotProduct);
        fragColor.a = DiffuseColor.a * alpha;
      })" );
    program->compileAndLink( );
    program->autocatching( );
  }
};

#endif /* __ICE_MATERIAL__ */
