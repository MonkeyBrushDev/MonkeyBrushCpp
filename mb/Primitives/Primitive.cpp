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

#include "Primitive.hpp"

namespace mb
{
  Primitive::Primitive( Primitive::Type type )
    : _type( type )
  {
    for( unsigned int i=0; i<VBO_LEN; ++i )
    {
      shaderDescriptors[i] = -1;
      VBO[i] = -1;
    }

    VAO = -1;
  }

  Primitive::~Primitive( void )
  {
    destroy();
  }


  Primitive::Type Primitive::getType( void ) const
  {
    return _type;
  }

  void Primitive::bindShaderAttrib( int vboIndex, GLint attrId )
  {
    shaderDescriptors[vboIndex] = attrId;
  }

  void Primitive::setupRender( void )
  {
    if( VAO == -1 )
    {
      glGenVertexArrays( 1, &VAO );
      glBindVertexArray( VAO );
      glGenBuffers( VBO_LEN, VBO );
      glBindVertexArray( NULL );
    }

    glBindVertexArray( VAO );

    //Vertices
    glBindBuffer( GL_ARRAY_BUFFER, VBO[VERTEX] );
    glBufferData( GL_ARRAY_BUFFER, sizeof(Vector3)*vertices.size(), vertices.data(), GL_STATIC_DRAW);
    if(shaderDescriptors[VERTEX] != -1)
    {
      glVertexAttribPointer( shaderDescriptors[VERTEX], 3, GL_FLOAT, GL_FALSE, 0, 0);
      glEnableVertexAttribArray(shaderDescriptors[VERTEX]);
    }

    //Color
    glBindBuffer( GL_ARRAY_BUFFER, VBO[COLOR] );
    glBufferData( GL_ARRAY_BUFFER, sizeof(Vector3)*color.size(), color.data(), GL_STATIC_DRAW);
    if(shaderDescriptors[COLOR] != -1)
    {
      glVertexAttribPointer( shaderDescriptors[COLOR], 3, GL_FLOAT, GL_FALSE, 0, 0);
      glEnableVertexAttribArray(shaderDescriptors[COLOR]);
    }

    //Normals
    glBindBuffer( GL_ARRAY_BUFFER, VBO[NORMAL] );
    glBufferData( GL_ARRAY_BUFFER, sizeof(Vector3)*normals.size(), normals.data(), GL_STATIC_DRAW);
    if(shaderDescriptors[NORMAL] != -1)
    {
      glVertexAttribPointer( shaderDescriptors[NORMAL], 3, GL_FLOAT, GL_FALSE, 0, 0);
      glEnableVertexAttribArray(shaderDescriptors[NORMAL]);
    }

    //Strips
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[INDEX]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort)*indices.size(), indices.data(), GL_STATIC_DRAW);

    //Texture coordinates
    glBindBuffer( GL_ARRAY_BUFFER, VBO[TEXCOORD] );
    glBufferData( GL_ARRAY_BUFFER, sizeof(Vector2)*texCoords.size(), texCoords.data(), GL_STATIC_DRAW);
    if(shaderDescriptors[TEXCOORD] != -1)
    {
      glVertexAttribPointer( shaderDescriptors[TEXCOORD], 2, GL_FLOAT, GL_FALSE, 0, 0);
      glEnableVertexAttribArray(shaderDescriptors[TEXCOORD]);
    }


    glBindVertexArray(NULL);

  }

  void Primitive::render( void )
  {
    //std::cout << "\t-Primitive '" << name << "'" << std::endl;
    glBindVertexArray(VAO);

    glEnable( GL_DEPTH_TEST );
    glDepthMask( GL_FALSE );
    glDisable( GL_CULL_FACE );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    switch (_type)
    {
        case Type::POINTS:
            glDrawElements( GL_POINTS, sizeof(GLushort)*indices.size(),
                            GL_UNSIGNED_SHORT, 0);
            break;
        case Type::LINES:
            glDrawElements( GL_LINES, sizeof(GLushort)*indices.size(),
                        GL_UNSIGNED_SHORT, 0);
            break;
        case Type::LINE_LOOP:
            glDrawElements( GL_LINE_LOOP, sizeof(GLushort)*indices.size(),
                        GL_UNSIGNED_SHORT, 0);
            break;
        case Type::LINE_STRIP:
            glDrawElements( GL_LINE_STRIP, sizeof(GLushort)*indices.size(),
                        GL_UNSIGNED_SHORT, 0);
            break;
    case Type::TRIANGLES:
        glDrawElements( GL_TRIANGLES, sizeof(GLushort)*indices.size(),
                    GL_UNSIGNED_SHORT, 0);
        break;
        case Type::TRIANGLE_FAN:
            glDrawElements( GL_TRIANGLE_FAN, sizeof(GLushort)*indices.size(),
                        GL_UNSIGNED_SHORT, 0);
            break;
        case Type::TRIANGLE_STRIP:
            glDrawElements( GL_TRIANGLE_STRIP, sizeof(GLushort)*indices.size(),
                        GL_UNSIGNED_SHORT, 0);
            break;
        case Type::QUADS:
            glDrawElements( GL_QUADS, sizeof(GLushort)*indices.size(),
                        GL_UNSIGNED_SHORT, 0);
            break;
        case Type::QUAD_STRIP:
            glDrawElements( GL_QUAD_STRIP, sizeof(GLushort)*indices.size(),
                        GL_UNSIGNED_SHORT, 0);
            break;
        default:
            break;
    }

    glEnable(GL_CULL_FACE);
    glDisable(GL_BLEND);

    glBindVertexArray(NULL);
  }

  void Primitive::destroy( void )
  {
    glBindBuffer(GL_ARRAY_BUFFER, NULL);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
    glDeleteBuffers(VBO_LEN, VBO);

    glBindVertexArray(NULL);
    glDeleteVertexArrays(1, &VAO);
    VAO = -1;
  }
}
