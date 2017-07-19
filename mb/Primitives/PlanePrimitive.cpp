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
  PlanePrimitive::PlanePrimitive(float width, float height,
    unsigned int widthSegments, unsigned int heightSegments ,
                                 Type type, TDrawType typeDraw )
  : Primitive( type, typeDraw )
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

    MAXPOINTS = vertices.size( );

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
  }
}
