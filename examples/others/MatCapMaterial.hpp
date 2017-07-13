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

#ifndef __MATCAPMATERIAL__
#define __MATCAPMATERIAL__

#include <mb/mb.h>

/* Example
mb::Texture2D* matcapTex = mb::Texture2D::loadFromImage( "green_matcap.jpg" );
MatCapMaterial* customMaterial = new MatCapMaterial( );
customMaterial->setMatcapMap( matcapTex );
*/
class MatCapMaterial : public mb::Material
{
public:
  MatCapMaterial( void )
  : Material( )
  {
    this->addStandardUniforms( );

    _matcapMap = std::make_shared< mb::TextureUniform >( );

    this->addUniform( matcapMapUnifName, _matcapMap );

    program = std::make_shared< mb::Program >( );
    program->loadVertexShaderFromText( R"(
      #version 330 core
      layout (location = 0) in vec3 position;
      layout (location = 1) in vec3 normal;

      out vec2 uvCap;

      uniform mat4 MB_MATRIXM;
      uniform mat4 MB_MATRIXV;
      uniform mat4 MB_MATRIXP;

      #import<MatCap.glsl>

      void main()
      {
        vec3 viewPos = -transpose(mat3(MB_MATRIXV)) * MB_MATRIXV[3].xyz;
        gl_Position = MB_MATRIXP * MB_MATRIXV * MB_MATRIXM * vec4(position, 1.0f);
        mat3 normalMatrix = mat3(inverse(transpose(MB_MATRIXV * MB_MATRIXM)));
        uvCap = matcap(viewPos, normalize(normalMatrix * normal));
      })" );
    program->loadFragmentShaderFromText( R"(
      #version 330 core

      in vec2 uvCap;

      out vec4 fragColor;

      uniform sampler2D MatCapTexture;

      void main( void )
      {
        fragColor = vec4( texture(MatCapTexture, uvCap).rgb, 1.0 );
      })" );
    program->compileAndLink( );
    program->autocatching( );
  }
  void setMatcapMap( mb::Texture2D *texture )
  {
    _matcapMap->value( texture );
  }
protected:
  mb::UniformPtr _matcapMap;
private:
  const char* matcapMapUnifName = "MatCapTexture";
};

#endif /* __MATCAPMATERIAL__ */
