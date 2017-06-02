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

#ifndef __MB_PRIMITIVE__
#define __MB_PRIMITIVE__

#include <string>
#include <iostream>
#include <mb/api.h>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "../Maths/Vector2.hpp"
#include "../Maths/Vector3.hpp"

namespace mb
{
  class Primitive
  {
  public:
    enum class Type: short
    {
      POINTS = 0,
      LINES,
      LINE_LOOP,
      LINE_STRIP,
      TRIANGLES,
      TRIANGLE_FAN,
      TRIANGLE_STRIP, 
      QUADS,
      QUAD_STRIP
    };

    typedef enum VBOAttrib
    {
      VERTEX = 0,
      COLOR,
      NORMAL,
      INDEX,      
      //TEXCOORD,
      VBO_LEN

    } TVBOAttrib;

    MB_API
    Primitive( Primitive::Type type = Primitive::Type::TRIANGLES );

    MB_API
    virtual ~Primitive( void );

    MB_API
    Primitive::Type getType( void ) const;

    MB_API
    GLuint getVAO( void ) const { return VAO; }

    MB_API
    void bindShaderAttrib( int vboIndex, GLint attrId );

    MB_API
    void setupRender( void );

    MB_API
    void render( void );

    MB_API
    void destroy( void );

  protected:
    
    GLuint VBO[VBO_LEN];
    GLuint VAO;
    GLint shaderDescriptors[VBO_LEN];

    Primitive::Type _type;

    std::vector<Vector3> vertices;
    std::vector<GLushort> indices;
    std::vector<Vector3> normals;
    std::vector<Vector2> texCoords;
    std::vector<Vector3> color;
  };
}//NS

#endif /* __MB_PRIMITIVE__ */
