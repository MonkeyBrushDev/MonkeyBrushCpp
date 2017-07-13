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

#ifndef __TEXTURE_SCROLL_MATERIAL__
#define __TEXTURE_SCROLL_MATERIAL__

#include <mb/mb.h>

class TextureScrollMaterial : public mb::Material
{
public:
  // REQUIRED TEXTURE REPEAT MODE
  TextureScrollMaterial( void )
  : Material( )
  {
    this->addStandardUniforms( );

    _colorMap = std::make_shared< mb::TextureUniform >( );

    this->addUniform( colorMapUnifName, _colorMap );

    this->addUniform( "ScrollXSpeed",
      std::make_shared< mb::FloatUniform >( ) );
    this->addUniform( "ScrollYSpeed",
      std::make_shared< mb::FloatUniform >( ) );
    this->addUniform( "_Time",
      std::make_shared< mb::FloatUniform >( ) );

    program = new mb::Program( );
    program->loadVertexShaderFromText( R"(
      #version 330 core
      layout (location = 0) in vec3 position;
      layout (location = 2) in vec2 uv;

      out vec2 outUV;

      uniform mat4 MB_MATRIXM;
      uniform mat4 MB_MATRIXV;
      uniform mat4 MB_MATRIXP;

      void main()
      {
        gl_Position = MB_MATRIXP * MB_MATRIXV * MB_MATRIXM * vec4(position, 1.0);
        outUV = uv;
      })" );
    program->loadFragmentShaderFromText( R"(
      #version 330 core
      in vec2 outUV;

      out vec4 fragColor;

      uniform sampler2D DiffuseTexture;
      uniform float ScrollXSpeed;
      uniform float ScrollYSpeed;
      uniform float _Time;

      void main( void )
      {
        // Create a separate variable to store our UVs
        // before we pass them to the texture() function
        vec2 scrolledUV = outUV;

        // Create variables that store the individual x and y
        // components for the UV's scaled by time
        float xScrollValue = ScrollXSpeed * _Time;
        float yScrollValue = ScrollYSpeed * _Time;

        // Apply the final UV offset
        scrolledUV += vec2(xScrollValue, yScrollValue);

        // Apply textures and tint
        vec4 c = texture( DiffuseTexture, scrolledUV );
        fragColor.rgb = c.rgb;
        fragColor.a = c.a;
      })" );
    program->compileAndLink( );
    program->autocatching( );
  }
  void setColorMap( mb::Texture2D *texture )
  {
    _colorMap->value( texture );
  }
protected:
  mb::UniformPtr _diffuse;
private:
  const char* colorMapUnifName = "DiffuseTexture";
};

#endif /* __TEXTURE_SCROLL_MATERIAL__ */
