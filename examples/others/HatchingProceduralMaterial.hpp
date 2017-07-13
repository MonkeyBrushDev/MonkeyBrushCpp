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

#ifndef __HATCHINGPROCEDURAL_MATERIAL__
#define __HATCHINGPROCEDURAL_MATERIAL__

#include <mb/mb.h>

class HatchingProceduralMaterial : public mb::Material
{
public:
  HatchingProceduralMaterial( void )
  : Material( )
  {
    this->addStandardUniforms( );

    program = std::make_shared< mb::Program >( );
    program->loadVertexShaderFromText( R"(
      #version 330 core
      layout (location = 0) in vec3 position;
      layout (location = 1) in vec3 normal;

      out vec3 outPosition;
      out vec3 outNormal;
      out float V;

      uniform mat4 MB_MATRIXM;
      uniform mat4 MB_MATRIXV;
      uniform mat4 MB_MATRIXP;

      void main()
      {
        gl_Position = MB_MATRIXP * MB_MATRIXV * MB_MATRIXM * vec4(position, 1.0);
        vec3 outPosition = vec3(MB_MATRIXM * vec4(position, 1.0));
        V = outPosition.x + outPosition.y + outPosition.z;
        mat3 normalMatrix = mat3(inverse(transpose(MB_MATRIXM)));
        outNormal = normalize(normalMatrix * normal);
      })" );
    program->loadFragmentShaderFromText( R"(
      #version 330 core
      in vec3 outPosition;
      in vec3 outNormal;
      in float V;

      out vec4 fragColor;

      uniform mat4 MB_MATRIXV;

      const float base_freq = 0.7;

      void main( void )
      {
        vec3 viewPos = -transpose(mat3(MB_MATRIXV)) * MB_MATRIXV[3].xyz;
        vec3 N=normalize(outNormal);
        vec3 L = normalize(viewPos - outPosition);
        float dif=dot(N, L);

        float LightIntensity = dif;

        float dp = length(vec2(dFdx(V), dFdy(V)));
        float logdp = -log2(dp * 8.0);
        float ilogdp = floor(logdp);
        float stripes = exp2(ilogdp);

        float sawtooth = fract((V) * base_freq * stripes);
        float triangle = abs(2.0 * sawtooth - 1.0);

        float transition = logdp - ilogdp;

        // taper ends
        triangle = abs((1.0 + transition) * triangle - transition);

        const float edgew = 0.3; // width of smooth step

        float edge0 = clamp(LightIntensity - edgew, 0.0, 1.0);
        float edge1 = clamp(LightIntensity, 0.0, 1.0);
        float square = 1.0 - smoothstep(edge0, edge1, triangle);
        vec3 color = vec3(square);

        fragColor = vec4( color, 1.0 );
      })" );
    program->compileAndLink( );
    program->autocatching( );
  }
};

#endif /* __HATCHINGPROCEDURAL_MATERIAL__ */
