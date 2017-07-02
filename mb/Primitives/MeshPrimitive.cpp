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

#include "MeshPrimitive.hpp"

#include "../Includes.hpp"
#include "../Utils/ObjLoader.hpp"

namespace mb
{
  MeshPrimitive::MeshPrimitive( const std::string& fileName )
  {
    mb::ObjLoader::loadObj( fileName );

    // Vertices
    vertices = mb::ObjLoader::vertices;
    // Normals
    normals = mb::ObjLoader::normals;
    // TexCoords
    texCoords = mb::ObjLoader::texCoords;
    // Indices
    indices = mb::ObjLoader::indexData;

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

  void MeshPrimitive::render( void )
  {
    glBindVertexArray( VAO );

    glDrawElements( GL_TRIANGLES, sizeof( GLushort ) *indices.size( ),
      GL_UNSIGNED_SHORT, 0 );

    glBindVertexArray( 0 );
  }
}
