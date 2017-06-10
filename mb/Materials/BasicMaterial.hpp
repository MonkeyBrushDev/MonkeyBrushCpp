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

#ifndef __MB_BASICMATERIAL__
#define __MB_BASICMATERIAL__

#include <mb/api.h>

#include "../Rendering/Material.hpp"
#include "../Rendering/Texture.hpp"
#include "../Maths/Color.hpp"
#include "../Maths/Vector4.hpp"

namespace mb
{
  class BasicMaterial: public Material
  {
  public:
    MB_API
    BasicMaterial( void )
    : Material( )
    {
      this->addUniform( MB_PROJ_MATRIX,
        std::make_shared< mb::Matrix4Uniform >( ) );
      this->addUniform( MB_VIEW_MATRIX,
        std::make_shared< mb::Matrix4Uniform >( ) );
      this->addUniform( MB_MODEL_MATRIX,
        std::make_shared< mb::Matrix4Uniform >( ) );

      _diffuse = std::make_shared< mb::Vector4Uniform >( Vector4( 1.0f ) );

      this->addUniform( colorUnifName, _diffuse );

      program = new mb::Program( );
      program->loadVertexShaderFromText( R"(
        #version 330 core
        layout (location = 0) in vec3 position;
        layout (location = 1) in vec3 normal;

        out vec3 outPosition;
        out vec3 Normal;

        uniform mat4 mb_MatrixM;
        uniform mat4 mb_MatrixV;
        uniform mat4 mb_MatrixP;

        void main()
        {
          gl_Position = mb_MatrixP * mb_MatrixV * mb_MatrixM * vec4(position, 1.0f);
          outPosition = vec3( mb_MatrixM * vec4( position, 1.0 ) );
          Normal = normal;
        })" );
      program->loadFragmentShaderFromText( R"(
        #version 330 core

        in vec3 outPosition;
        in vec3 Normal;

        out vec4 fragColor;

        uniform vec4 DiffuseColor;
        uniform mat4 view;

        void main()
        {
          vec3 viewPos = -transpose(mat3(view)) * view[3].xyz;
          vec3 L = normalize(viewPos-outPosition);
          vec3 N = normalize( Normal );
          float dif = dot( N, L );
          dif = clamp( dif, 0.0, 1.0 );
          fragColor = vec4( DiffuseColor.rgb * dif, 1.0 ) + vec4( DiffuseColor.rgb * 0.3, 1.0 );
          fragColor.a = DiffuseColor.a;
        })" );
      program->compileAndLink( );
      program->autocatching( );
    }
    MB_API
    void setColor( const Color &color )
    {
      _diffuse->value( mb::Color( color.r( ), color.g( ), color.b( ), color.a( ) ) );
    }
  protected:
    mb::UniformPtr _diffuse;
  private:
    const char* colorUnifName = "DiffuseColor";
  };
}

#endif /* __MB_BASICMATERIAL__ */
