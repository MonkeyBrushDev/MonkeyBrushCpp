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

#include "BlackWhitePPMaterial.hpp"

namespace mb
{
  BlackWhitePPMaterial::BlackWhitePPMaterial( void )
    : mb::PostProcessMaterial( )
  {
    this->addUniform( "targetTex", std::make_shared< mb::TextureUniform > ( ) );

    program->loadFragmentShaderFromText(
    R"(#version 330 core
      // Samplers
      in vec2 uv;
      uniform sampler2D targetTex;

      uniform mat4 kernelMatrix;

      out vec4 fragColor;

      void main(void)
      {
        float luminance = dot(texture(targetTex, uv).rgb, vec3(0.3, 0.59, 0.11));
        fragColor = vec4(luminance, luminance, luminance, 1.0);
      })" );
    program->compileAndLink( );
    program->autocatching( );
  }
}
