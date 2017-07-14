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

#include "PointPrimitive.hpp"

#include "../Includes.hpp"

namespace mb
{
  PointCloudPrimitive::PointCloudPrimitive( const std::vector< Vector3 >& points )
  {
    vertices = points;

    MAXPOINTS = points.size( );

    for( unsigned int i=0; i < vertices.size(); ++i )
      indices.push_back( i );

    uint32_t VBO[ 1 ];
    glGenVertexArrays( 1, &VAO );
    glBindVertexArray( VAO );
    glGenBuffers( 1, VBO );

    glBindVertexArray( VAO );

    //Vertices
    glBindBuffer( GL_ARRAY_BUFFER, VBO[ 0 ] );
    glBufferData( GL_ARRAY_BUFFER, sizeof( Vector3 ) *vertices.size( ), vertices.data( ), GL_STATIC_DRAW );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, 0 );
    glEnableVertexAttribArray( 0 );

    glBindVertexArray( 0 );
  }

  void PointCloudPrimitive::render( void )
  {
    glBindVertexArray( VAO );

    glDrawArrays( GL_POINTS, 0, MAXPOINTS );

    glBindVertexArray( 0 );
  }
}
