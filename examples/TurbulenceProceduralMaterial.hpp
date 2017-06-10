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

#ifndef __TURBULENCEPROCEDURAL_MATERIAL__
#define __TURBULENCEPROCEDURAL_MATERIAL__

#include <mb/mb.h>

class TurbulenceProceduralMaterial : public mb::Material
{
public:
  TurbulenceProceduralMaterial( void )
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
      layout (location = 1) in vec3 normal;

      out vec3 outPosition;

      uniform mat4 mb_MatrixM;
      uniform mat4 mb_MatrixV;
      uniform mat4 mb_MatrixP;

      void main()
      {
        gl_Position = mb_MatrixP * mb_MatrixV * mb_MatrixM * vec4(position, 1.0);
        outPosition = vec3(mb_MatrixM * vec4(position, 1.0));
      })" );
    program->loadFragmentShaderFromText( R"(
      #version 330 core
      in vec3 outPosition;

      out vec4 fragColor;

      const float base_freq = 0.35;

      #import<SimpleNoise3D.glsl>

      const vec3 Color1 = vec3(0.8, 0.7, 0.0);
      const vec3 Color2 = vec3(0.6, 0.1, 0.0);

      void main( void )
      {
        vec4 noisevec;
        noisevec.x = snoise(outPosition * base_freq * 1.0) * 8.0;
        noisevec.y = snoise(outPosition * base_freq * 2.0) * 4.0;
        noisevec.z = snoise(outPosition * base_freq * 4.0) * 2.0;
        noisevec.w = snoise(outPosition * base_freq * 8.0) * 1.0;
        // noisevec = (noisevec / 8.0 + 1.0) / 2.0;
        noisevec = noisevec / 8.0;
        // noisevec = noisevec * noisevec;

        float intensity = abs(noisevec[0] - 0.20) +
                          abs(noisevec[1] - 0.10) +
                          abs(noisevec[2] - 0.05) +
                          abs(noisevec[3] - 0.025);

        intensity -= 0.3;

        vec3 color = mix(Color1, Color2, intensity);

        fragColor = vec4( color, 1.0 );
      })" );
    program->compileAndLink( );
    program->autocatching( );
  }
};

#endif /* __TURBULENCEPROCEDURAL_MATERIAL__ */
