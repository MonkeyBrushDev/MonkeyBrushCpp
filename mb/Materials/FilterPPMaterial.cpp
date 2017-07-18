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

#include "FilterPPMaterial.hpp"

namespace mb
{
  FilterPPMaterial::FilterPPMaterial( void )
    : mb::PostProcessMaterial( )
  {
    this->addUniform( "targetTex", std::make_shared< mb::TextureUniform > ( ) );
    this->addUniform( "kernelMatrix", std::make_shared< mb::Matrix4Uniform >( ) );

    program->loadFragmentShaderFromText(
    R"(#version 330 core
      // Samplers
      in vec2 uv;
      uniform sampler2D targetTex;

      uniform mat4 kernelMatrix;

      out vec4 fragColor;

      void main(void)
      {
        vec3 baseColor = texture(targetTex, uv).rgb;
        baseColor = (kernelMatrix * vec4(baseColor, 1.0)).rgb;

        fragColor = vec4(baseColor, 1.0);
      })" );
    program->compileAndLink( );
    program->autocatching( );
  }
}
