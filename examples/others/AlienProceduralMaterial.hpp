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

#ifndef __ALIENPROCEDURAL_MATERIAL__
#define __ALIENPROCEDURAL_MATERIAL__

#include <mb/mb.h>

class AlienProceduralMaterial : public mb::Material
{
public:
  AlienProceduralMaterial( void )
  : Material( )
  {
    this->addStandardUniforms( );

    program->loadVertexShaderFromText( R"(
      #version 330 core
      layout (location = 0) in vec3 position;
      layout (location = 1) in vec3 normal;

      out vec3 outPosition;

      uniform mat4 MB_MATRIXM;
      uniform mat4 MB_MATRIXV;
      uniform mat4 MB_MATRIXP;

      void main()
      {
        gl_Position = MB_MATRIXP * MB_MATRIXV * MB_MATRIXM * vec4(position, 1.0);
        outPosition = vec3(MB_MATRIXM * vec4(position, 1.0));
      })" );
    program->loadFragmentShaderFromText( R"(
      #version 330 core
      in vec3 outPosition;

      out vec4 fragColor;

      const float base_freq = 6.9;

      #import<SimpleNoise3D.glsl>

      const vec3 SkinColor1 = vec3(0.3, 0.5, 0.2);
      const vec3 SkinColor2 = vec3(0.8, 0.8, 0.5);
      const vec3 SkinColor3 = vec3(0.7, 0.8, 0.8);

      void main( void )
      {
        float noise =
            snoise(outPosition * base_freq) * 8.0 +
            snoise(outPosition * base_freq * 2.0) * 4.0 +
            snoise(outPosition * base_freq * 4.0) * 2.0 +
            snoise(outPosition * base_freq * 8.0);
        noise = (noise / 8.0 + 1.0) / 2.0;

        noise -= 0.3;
        noise *= 2.0;

        float intensity = noise;
        vec3 color;

        intensity = clamp(intensity, 0.0, 1.0);

        if ( intensity < 0.5 )
        {
          color = mix(SkinColor1, SkinColor2, intensity/0.5);
        }
        else
        {
          color = mix(SkinColor1, SkinColor3, (intensity - 0.5)/0.5);
        }

        fragColor = vec4( color, 1.0 );
      })" );
    program->compileAndLink( );
    program->autocatching( );
  }
};

#endif /* __ALIENPROCEDURAL_MATERIAL__ */
