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

#include "CubePrimitive.hpp"

#include "../Includes.hpp"

namespace mb
{
  CubePrimitive::CubePrimitive( float side )
  {
    float side2 = side / 2.0f;

  // Vertices
  vertices = std::vector<Vector3> {
    // Front
    Vector3( -side2, -side2, side2 ),
    Vector3( side2, -side2, side2 ),
    Vector3( side2,  side2, side2 ),
    Vector3( -side2,  side2, side2 ),
    // Right
    Vector3( side2, -side2, side2 ),
    Vector3( side2, -side2, -side2 ),
    Vector3( side2,  side2, -side2 ),
    Vector3( side2,  side2, side2 ),
    // Back
    Vector3( -side2, -side2, -side2 ),
    Vector3( -side2,  side2, -side2 ),
    Vector3( side2,  side2, -side2 ),
    Vector3( side2, -side2, -side2 ),
    // Left
    Vector3( -side2, -side2, side2 ),
    Vector3( -side2,  side2, side2 ),
    Vector3( -side2,  side2, -side2 ),
    Vector3( -side2, -side2, -side2 ),
    // Bottom
    Vector3( -side2, -side2, side2 ),
    Vector3( -side2, -side2, -side2 ),
    Vector3( side2, -side2, -side2 ),
    Vector3( side2, -side2, side2 ),
    // Top
    Vector3( -side2,  side2, side2 ),
    Vector3( side2,  side2, side2 ),
    Vector3( side2,  side2, -side2 ),
    Vector3( -side2,  side2, -side2 )
  };
  // Normals
  normals = std::vector<Vector3> {
    // Front
    Vector3( 0.0, 0.0, 1.0 ),
    Vector3( 0.0, 0.0, 1.0 ),
    Vector3( 0.0, 0.0, 1.0 ),
    Vector3( 0.0, 0.0, 1.0 ),
    // Right
    Vector3( 1.0, 0.0, 0.0 ),
    Vector3( 1.0, 0.0, 0.0 ),
    Vector3( 1.0, 0.0, 0.0 ),
    Vector3( 1.0, 0.0, 0.0 ),
    // Back
    Vector3( 0.0, 0.0, -1.0 ),
    Vector3( 0.0, 0.0, -1.0 ),
    Vector3( 0.0, 0.0, -1.0 ),
    Vector3( 0.0, 0.0, -1.0 ),
    // Left
    Vector3( -1.0, 0.0, 0.0 ),
    Vector3( -1.0, 0.0, 0.0 ),
    Vector3( -1.0, 0.0, 0.0 ),
    Vector3( -1.0, 0.0, 0.0 ),
    // Bottom
    Vector3( 0.0, -1.0, 0.0 ),
    Vector3( 0.0, -1.0, 0.0 ),
    Vector3( 0.0, -1.0, 0.0 ),
    Vector3( 0.0, -1.0, 0.0 ),
    // Top
    Vector3( 0.0, 1.0, 0.0 ),
    Vector3( 0.0, 1.0, 0.0 ),
    Vector3( 0.0, 1.0, 0.0 ),
    Vector3( 0.0, 1.0, 0.0 )
  };
  // TexCoords
  texCoords = std::vector<Vector2> {
    // Front
    Vector2( 0.0, 0.0 ),
    Vector2( 1.0, 0.0 ),
    Vector2( 1.0, 1.0 ),
    Vector2( 0.0, 1.0 ),
    // Right
    Vector2( 0.0, 0.0 ),
    Vector2( 1.0, 0.0 ),
    Vector2( 1.0, 1.0 ),
    Vector2( 0.0, 1.0 ),
    // Back
    Vector2( 0.0, 0.0 ),
    Vector2( 1.0, 0.0 ),
    Vector2( 1.0, 1.0 ),
    Vector2( 0.0, 1.0 ),
    // Left
    Vector2( 0.0, 0.0 ),
    Vector2( 1.0, 0.0 ),
    Vector2( 1.0, 1.0 ),
    Vector2( 0.0, 1.0 ),
    // Bottom
    Vector2( 0.0, 0.0 ),
    Vector2( 1.0, 0.0 ),
    Vector2( 1.0, 1.0 ),
    Vector2( 0.0, 1.0 ),
    // Top
    Vector2( 0.0, 0.0 ),
    Vector2( 1.0, 0.0 ),
    Vector2( 1.0, 1.0 ),
    Vector2( 0.0, 1.0 )
  };
  // Indices
  indices = std::vector< short > {
    0, 1, 2, 0, 2, 3,
    4, 5, 6, 4, 6, 7,
    8, 9, 10, 8, 10, 11,
    12, 13, 14, 12, 14, 15,
    16, 17, 18, 16, 18, 19,
    20, 21, 22, 20, 22, 23
  };

    uint32_t VBO[ 4 ];
    glGenVertexArrays( 1, &VAO );
    glBindVertexArray( VAO );
    glGenBuffers( 4, VBO );

    glBindVertexArray( VAO );

    //Vertices
    glBindBuffer( GL_ARRAY_BUFFER, VBO[ 0 ] );
    glBufferData( GL_ARRAY_BUFFER, sizeof( Vector3 ) *vertices.size( ), vertices.data( ), GL_STATIC_DRAW );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, 0 );
    glEnableVertexAttribArray( 0 );

    //Normals
    glBindBuffer( GL_ARRAY_BUFFER, VBO[ 1 ] );
    glBufferData( GL_ARRAY_BUFFER, sizeof( Vector3 ) *normals.size( ), normals.data( ), GL_STATIC_DRAW );
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, 0 );
    glEnableVertexAttribArray( 1 );

    //Texture coordinates
    glBindBuffer( GL_ARRAY_BUFFER, VBO[ 2 ] );
    glBufferData( GL_ARRAY_BUFFER, sizeof( Vector2 ) *texCoords.size( ), texCoords.data( ), GL_STATIC_DRAW );
    glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 0, 0 );
    glEnableVertexAttribArray( 2 );

    //Strips
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, VBO[ 3 ] );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( GLushort ) *indices.size( ), indices.data( ), GL_STATIC_DRAW );

    glBindVertexArray( 0 );
  }

  void CubePrimitive::render( void )
  {
    glBindVertexArray( VAO );

    glDrawElements( GL_TRIANGLES, sizeof( GLushort ) *indices.size( ),
      GL_UNSIGNED_SHORT, 0 );

    glBindVertexArray( 0 );
  }
}
