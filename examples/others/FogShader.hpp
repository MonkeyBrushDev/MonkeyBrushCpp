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

#ifndef __FOG_SHADER__
#define __FOG_SHADER__

const char* VS_FOG_SHADER = R"(
#version 330 core
layout (location = 0) in vec3 Vertex;

uniform mat4 MB_MATRIXM;
uniform mat4 MB_MATRIXV;
uniform mat4 MB_MATRIXP;

out vec3 position;

void main()
{
  gl_Position = MB_MATRIXP * MB_MATRIXV * MB_MATRIXM * vec4(Vertex, 1.0);
  position = vec3( MB_MATRIXV * MB_MATRIXM * vec4( Vertex, 1.0 ) );
})";

const char* FS_FOG_SHADER = R"(
#version 330 core
in vec3 position;
out vec4 fragColor;

uniform float density;
uniform mat4 MB_MATRIXV;

uniform vec3 fogColor;
const vec3 color = vec3( 1.0, 0.3, 0.4 );

void main()
{
  vec3 viewPos = -transpose(mat3(MB_MATRIXV)) * MB_MATRIXV[3].xyz;
  float dst = length(position - viewPos);
  float fogFactor = 1.0 / exp(dst * density);
  fogFactor = clamp(fogFactor, 0.0, 1.0);
  fragColor = vec4(mix(fogColor, color, fogFactor), 1.0);
})";

#endif
