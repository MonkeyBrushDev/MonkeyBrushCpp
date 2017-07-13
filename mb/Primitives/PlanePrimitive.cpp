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

#include "PlanePrimitive.hpp"

#include "../Includes.hpp"

namespace mb
{
  PlanePrimitive::PlanePrimitive( float width, float height,
    unsigned int widthSegments, unsigned int heightSegments )
  {
    float width_half = width / 2.0f;
    float height_half = height / 2.0f;

    unsigned int gridX = std::floor( widthSegments );// || 1.0f;
    unsigned int gridY = std::floor( heightSegments );// || 1.0f;

    unsigned int gridX1 = gridX + 1;
    unsigned int gridY1 = gridY + 1;

    float segment_width = width / gridX;
    float segment_height = height / gridY;

    unsigned int ix, iy;

    for( iy = 0; iy < gridY1; ++iy )
    {
      float y = iy * segment_height - height_half;
      for( ix = 0; ix < gridX1; ++ix )
      {
        float x = ix * segment_width - width_half;

        vertices.push_back( Vector3( x, -y, 0.0f ) );
        normals.push_back( Vector3( 0.0f, 0.0f, 1.0f ) );

        texCoords.push_back( Vector2( ( ( float ) ix ) / gridX, 1.0 - (( ( float ) iy ) / gridY ) ) );
      }
    }

    for( iy = 0; iy < gridY; ++iy )
    {
      for( ix = 0; ix < gridX; ++ix )
      {
        unsigned int a = ix + gridX1 * iy;
        unsigned int b = ix + gridX1 * ( iy + 1 );
        unsigned int c = ( ix + 1 ) + gridX1 * ( iy + 1 );
        unsigned int d = ( ix + 1 ) + gridX1 * iy;

        // faces
        indices.push_back( a );   indices.push_back( b );    indices.push_back( d );
        indices.push_back( b );   indices.push_back( c );    indices.push_back( d );
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

  void PlanePrimitive::render( void )
  {
    glBindVertexArray( VAO );

    glDrawElements( GL_TRIANGLES, sizeof( GLushort ) *indices.size( ),
      GL_UNSIGNED_SHORT, 0 );

    glBindVertexArray( 0 );
  }
}
