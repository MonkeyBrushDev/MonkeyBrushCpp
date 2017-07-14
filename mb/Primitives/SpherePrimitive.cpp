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
  SpherePrimitive::SpherePrimitive( float radius, unsigned int width,
                                    unsigned int height, Type type, TDrawType typeDraw )
  : Primitive( type, typeDraw )
  {
    // -- Creating geometry of the sphere -- //
    //unsigned int faces = ( 1 + height ) * ( 1 + width );
    //unsigned int nv = 3 * height * width * 2;

    // Generating the vertex data...
    //unsigned int NVIDX = 0;
    //unsigned int NNIDX = 0;
    //unsigned int NTIDX = 0;
    unsigned int IDX = 0;

    std::vector< std::vector< unsigned int > > grid;
    float u, v;
    Vector3 vertex;

    for ( unsigned int iy = 0; iy <= height; ++iy )
    {
      std::vector< unsigned int> idxs;
      v = ( float ) iy / ( float ) height;

      for ( unsigned int ix = 0; ix <= width; ++ix )
      {
        u = ( float ) ix / ( float ) width;

        float x = ( -radius * cos( u * Mathf::TWO_PI ) * sin( v * Mathf::PI ) );
        float y = ( radius * cos( v * Mathf::PI ) );
        float z = ( radius * sin( u * Mathf::TWO_PI ) * sin( v * Mathf::PI ) );

        vertex = Vector3( x, y, z );
        vertices.push_back( vertex );

        vertex.normalize( );
        normals.push_back( vertex );

        texCoords.push_back( Vector2( u, /*1.0f - */v ) ); // (u,v)

        idxs.push_back( IDX++ );
      }
      grid.push_back( idxs );
    }

    MAXPOINTS = vertices.size( );

    //Sorting of indices...(for triangles-strip)
    for ( unsigned int iy = 0; iy < height; ++iy )
    {
      for ( unsigned int ix = 0; ix < width; ++ix )
      {
        unsigned int a = grid[ iy ][ ix + 1 ];
        unsigned int b = grid[ iy ][ ix ];
        unsigned int c = grid[ iy + 1 ][ ix ];
        unsigned int d = grid[ iy + 1 ][ ix + 1 ];

        indices.push_back( a );
        indices.push_back( b );
        indices.push_back( d );

        indices.push_back( b );
        indices.push_back( c );
        indices.push_back( d );
      }
    }
  }

}
