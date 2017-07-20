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

#include "TorusPrimitive.hpp"

#include "../Includes.hpp"

namespace mb
{
 TorusPrimitive::TorusPrimitive( float outerRadius, float innerRadius,
                unsigned int sides, unsigned int rings, Primitive::Type type,
                Primitive::TDrawType typeDraw )
 : Primitive( type, typeDraw )
 {
     // Generate the vertex data
     float ringFactor = (Mathf::PI * 2.0) / (float)rings;
     float sideFactor = (Mathf::PI * 2.0) / (float)sides;

     Vector3 norms (0, 0, 0);
     for( unsigned int ring = 0; ring <= rings; ++ring )
     {
       float u  = ring * ringFactor;
       float cu = cos(u);
       float su = sin(u);

       for( unsigned int side = 0; side < sides; ++side )
       {
           float v  = side * sideFactor;
           float cv = cos(v);
           float sv = sin(v);
           float r  = ( outerRadius + innerRadius * cv );

           norms[0] = cv * cu * r;
           norms[1] = sv * su *r;
           norms[2] = sv * r;

           // Normalize
           float len = sqrt( norms[0] * norms[0] +
                             norms[1] * norms[1] +
                             norms[2] * norms[2] );

           norms[0] /= len;
           norms[1] /= len;
           norms[2] /= len;

           vertices.push_back(Vector3( r * cu, r * su, innerRadius * sv ));
           normals.push_back(Vector3( norms[0], norms[1], norms[2] ));
           texCoords.push_back(Vector2( u / (Mathf::PI * 2.0), v / (Mathf::PI * 2.0)));
       }
     }

     for( unsigned int ring = 0; ring < rings; ++ring )
     {
         int ringStart = ring * sides;
         int nextRingStart = (ring + 1) * sides;
         for( unsigned int side = 0; side < sides; ++side)
         {
             int nextSide = (side + 1) % sides;

             //Building quads
             indices.push_back( ringStart + side );
             indices.push_back( nextRingStart + side );
             indices.push_back( nextRingStart + nextSide );
             indices.push_back( ringStart + side );
             indices.push_back( nextRingStart + nextSide );
             indices.push_back( ringStart + nextSide );
         }
     }

     MAXPOINTS = vertices.size();

 }

}
