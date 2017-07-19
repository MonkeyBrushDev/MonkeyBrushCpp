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

#include "ToneMappingMaterial.hpp"

namespace mb
{
  ToneMappingMaterial::ToneMappingMaterial( TonemappingOperator op )
    : mb::PostProcessMaterial( )
  {
    this->addUniform( "targetTex", std::make_shared< mb::TextureUniform > ( ) );
    this->addUniform( "_ExposureAdjustment", std::make_shared< mb::FloatUniform > ( 1.0f ) );
    std::string headers_defines;
    switch ( op )
    {
      case TonemappingOperator::Hable:
        headers_defines += "#define HABLE_TONEMAPPING\n";
        break;
      case TonemappingOperator::Reinhard:
        headers_defines += "#define REINHARD_TONEMAPPING\n";
        break;
      case TonemappingOperator::HejiDawson:
        headers_defines += "#define OPTIMIZED_HEJIDAWSON_TONEMAPPING\n";
        break;
      case TonemappingOperator::Photographic:
        headers_defines += "#define PHOTOGRAPHIC_TONEMAPPING\n";
        break;
    }

    program->loadFragmentShaderFromText(
    R"(#version 330 core
    )" + headers_defines + R"(
      // Samplers
      in vec2 uv;
      uniform sampler2D targetTex;

      out vec4 fragColor;

      // Constants
      uniform float _ExposureAdjustment;

      #if defined(HABLE_TONEMAPPING)
        const float A = 0.15;
        const float B = 0.50;
        const float C = 0.10;
        const float D = 0.20;
        const float E = 0.02;
        const float F = 0.30;
        const float W = 11.2;
      #endif

      float Luminance(vec3 c)
      {
        return dot(c, vec3(0.22, 0.707, 0.071));
      }

      void main(void)
      {
        vec3 colour = texture(targetTex, uv).rgb;
      #if defined(REINHARD_TONEMAPPING)
        float lum = Luminance(colour.rgb);
        float lumTm = lum * _ExposureAdjustment;
        float scale = lumTm / (1.0 + lumTm);

        colour *= scale / lum;
      #elif defined(HABLE_TONEMAPPING)
        colour *= _ExposureAdjustment;

        const float ExposureBias = 2.0;
        vec3 x = ExposureBias * colour;

        vec3 curr = ((x * (A * x + C * B) + D * E) / (x * (A * x + B) + D * F)) - E / F;

        x = vec3(W, W, W);
        vec3 whiteScale = 1.0 / (((x * (A * x + C * B) + D * E) / (x * (A * x + B) + D * F)) - E / F);
        colour = curr * whiteScale;
      #elif defined(OPTIMIZED_HEJIDAWSON_TONEMAPPING)
        colour *= _ExposureAdjustment;

        vec3 X = max(vec3(0.0, 0.0, 0.0), colour - 0.004);
        vec3 retColor = (X * (6.2 * X + 0.5)) / (X * (6.2 * X + 1.7) + 0.06);

        colour = retColor * retColor;
      #elif defined(PHOTOGRAPHIC_TONEMAPPING)
        colour =  vec3(1.0, 1.0, 1.0) - exp2(-_ExposureAdjustment * colour);
      #endif

        fragColor = vec4(colour.rgb, 1.0);
      })" );
    program->compileAndLink( );
    program->autocatching( );
  }
}
