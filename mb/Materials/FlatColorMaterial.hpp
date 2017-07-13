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

#ifndef __MB_FLAT_MATERIAL__
#define __MB_FLAT_MATERIAL__

#include <mb/api.h>

#include "../Rendering/Material.hpp"
#include "../Rendering/Texture.hpp"
#include "../Maths/Color.hpp"
#include "../Maths/Vector4.hpp"

namespace mb
{
  class FlatColorMaterial: public Material
  {
  public:
    MB_API
    FlatColorMaterial( void )
    : Material( )
    {
      this->addStandardUniforms( );

      _diffuse = std::make_shared< mb::Vector4Uniform >( Vector4( 1.0f ) );

      this->addUniform( "DiffuseColor", _diffuse );

      program = std::make_shared< mb::Program >( );
      program->loadVertexShaderFromText( R"(
        #version 330 core
        layout (location = 0) in vec3 attrPosition;
        layout (location = 1) in vec3 attrNormal;

        out vec3 outPosition;
        flat out vec3 outNormal;

        uniform mat4 MB_MATRIXM;
        uniform mat4 MB_MATRIXV;
        uniform mat4 MB_MATRIXP;

        void main( void )
      {
        vec3 normal = vec3( attrNormal );
        mat3 normalMatrix = mat3( inverse( transpose( MB_MATRIXV * MB_MATRIXM ) ) );
        vec3 transformedNormal = normalMatrix * normal;
        vec3 position = vec3( attrPosition );
        outPosition = vec3( MB_MATRIXV * MB_MATRIXM * vec4( position, 1.0 ) );
        outNormal = normalize( attrNormal );
        gl_Position = MB_MATRIXP * vec4( outPosition, 1.0 );
      })" );
      program->loadFragmentShaderFromText( R"(
        #version 330 core

        in vec3 outPosition;
        flat in vec3 outNormal;

        out vec4 fragColor;

        uniform vec4 DiffuseColor;
        uniform mat4 view;

        vec4 shading( )
        {
          vec3 viewPos = -transpose(mat3(view)) * view[3].xyz;
          vec3 L = normalize(viewPos - outPosition);
          vec3 N = normalize( outNormal );
          float dif = dot( N, L );
          dif = clamp( dif, 0.0, 1.0 );
          return vec4( DiffuseColor.rgb * ( dif + 0.3 ), DiffuseColor.a );
        }
        void main()
        {
          fragColor = shading( );
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
  };
}

#endif /* __MB_FLAT_MATERIAL__ */
