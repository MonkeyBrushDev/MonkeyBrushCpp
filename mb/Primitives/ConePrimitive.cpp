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

#include "ConePrimitive.hpp"

#include "../Exceptions/RuntimeException.hpp"

namespace mb
{
  ConePrimitive::ConePrimitive( float bottomRadius, float topRadius,
    float height, unsigned int radialSubDiv, unsigned int heightSubDiv,
    bool createTopBase, bool createBottomBase,
    Primitive::Type type,
    Primitive::TDrawType typeDraw )
    : Primitive( type, typeDraw )
  {
    if ( radialSubDiv < 3 )
    {
      throw RuntimeException( "radialSubDiv must be 3 or greater" );
    }

    if ( heightSubDiv < 1 )
    {
      throw RuntimeException( "heightSubDiv must be 1 or greater" );
    }

    const unsigned int extra = ( createTopBase ? 2 : 0 ) + ( createBottomBase ? 2 : 0 );
    const unsigned int vertsAroundEdge = radialSubDiv + 1;

    const float slantH = atan2( bottomRadius - topRadius, height );
    const float cSlantH = cos( slantH );
    const float sSlantH = sin( slantH );

    const int start = createTopBase ? -2 : 0;
    const int end = heightSubDiv + ( createBottomBase ? 2 : 0 );

    for ( int yy = start; yy <= end; ++yy )
    {
      float v = yy / ( float ) heightSubDiv;
      float y = height * v;
      float ringRadius;
      if ( yy < 0 )
      {
        y = 0.0f;
        v = 1.0f;
        ringRadius = bottomRadius;
      }
      else if ( yy > (int)heightSubDiv )
      {
        y = height;
        v = 1.0f;
        ringRadius = topRadius;
      }
      else
      {
        ringRadius = bottomRadius +
          ( topRadius - bottomRadius ) * ( yy / ( float ) heightSubDiv );
      }
      if ( y == -2 || yy == (int)heightSubDiv + 2 )
      {
        ringRadius = 0.0f;
        v = 0.0f;
      }
      y -= height / 2.0f;

      for ( unsigned int ii = 0; ii < vertsAroundEdge; ++ii )
      {
        float sn = sin( ii * Mathf::PI * 2.0f / ( float ) radialSubDiv );
        float cs = cos( ii * Mathf::PI * 2.0f / ( float ) radialSubDiv );

        vertices.push_back( Vector3( sn * ringRadius, y, cs * ringRadius ) );
        normals.push_back( Vector3( ( yy < 0 || yy > (int)heightSubDiv ) ? 0.0f : ( sn * cSlantH ),
          ( yy < 0 ) ? -1.0f : ( ( yy > (int)heightSubDiv ) ? 1.0f : sSlantH ),
          ( yy < 0 || yy > (int)heightSubDiv ) ? 0.0f : ( cs * cSlantH ) ) );
        texCoords.push_back( Vector2( ( ii / ( float ) radialSubDiv ), 1.0f - v ) );
      }
    }

    for ( unsigned int yy = 0; yy < heightSubDiv + extra; ++yy )
    for ( unsigned int ii = 0; ii < radialSubDiv; ++ii )
    {
      indices.push_back( vertsAroundEdge * ( yy + 0 ) + 0 + ii );
      indices.push_back( vertsAroundEdge * ( yy + 0 ) + 1 + ii );
      indices.push_back( vertsAroundEdge * ( yy + 1 ) + 1 + ii );

      indices.push_back( vertsAroundEdge * ( yy + 0 ) + 0 + ii );
      indices.push_back( vertsAroundEdge * ( yy + 1 ) + 1 + ii );
      indices.push_back( vertsAroundEdge * ( yy + 1 ) + 0 + ii );
    }

    MAXPOINTS = vertices.size( );
  }
}
