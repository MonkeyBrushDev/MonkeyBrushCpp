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

#include "SpherePrimitive.hpp"

#include "../Includes.hpp"

namespace mb
{
  SpherePrimitive::SpherePrimitive( float radius, unsigned int width, unsigned int height )
  {
    // -- Creating geometry of the sphere -- //
    unsigned int faces = ( 1 + height ) * ( 1 + width );
    unsigned int nv = 3 * height * width * 2;

    // Generating the vertex data...
    unsigned int NVIDX = 0;
    unsigned int NNIDX = 0;
    unsigned int NTIDX = 0;
    unsigned int IDX = 0;

    std::vector< std::vector< unsigned int > > grid;
    float u, v;
    Vector3 vertex;

    for ( unsigned int i = 0; i <= height; ++i )
    {
      std::vector< unsigned int> idxs;
      v = ( float ) i / ( float ) height;

      for ( unsigned int j = 0; j <= width; ++j )
      {
        u = ( float ) j / ( float ) width;

        float x = ( -radius * cos( u * Mathf::TWO_PI ) * sin( v * Mathf::TWO_PI ) );
        float y = ( radius * cos( v * Mathf::TWO_PI ) );
        float z = ( radius * sin( u * Mathf::TWO_PI ) * sin( v * Mathf::TWO_PI ) );

        vertex = Vector3( x, y, z );
        vertices.push_back( vertex );

        vertex.normalize( );
        normals.push_back( vertex );

        texCoords.push_back( Vector2( u, 1.0f - v ) ); // (u,v)

        idxs.push_back( IDX++ );
      }
      grid.push_back( idxs );
    }

    //Sorting of indices...(for triangles-strip)
    for ( unsigned int i = 0; i < height; ++i )
    {
      for ( unsigned int j = 0; j < width; ++j )
      {
        unsigned int a = grid[ i ][ j + 1 ];
        unsigned int b = grid[ i ][ j ];
        unsigned int c = grid[ i + 1 ][ j ];
        unsigned int d = grid[ i + 1 ][ j + 1 ];

        indices.push_back( a );
        indices.push_back( b );
        indices.push_back( d );

        indices.push_back( b );
        indices.push_back( c );
        indices.push_back( d );
      }
    }

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

  void SpherePrimitive::render( void )
  {
    glBindVertexArray( VAO );

    glDrawElements( GL_TRIANGLES, sizeof( GLushort ) *indices.size( ),
      GL_UNSIGNED_SHORT, 0 );

    glBindVertexArray( 0 );
  }
}
