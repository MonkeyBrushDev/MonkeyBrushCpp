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

#include "CapsulePrimitive.hpp"

namespace mb
{

  CapsulePrimitive::CapsulePrimitive( float radius, float height,
    unsigned int subHeight, unsigned int numSegm,
    Primitive::Type type,
    Primitive::TDrawType typeDraw )
    : Primitive( type, typeDraw )
  {
    const unsigned int ringsBody = subHeight + 1;
    const unsigned int ringsTotal = subHeight + ringsBody;

    const float bodyIncr = 1.0f / ( float ) ( ringsBody - 1 );
    const float ringIncr = 1.0f / ( float ) ( subHeight - 1 );

    float r = 0.0f;
    for ( r = 0; r < subHeight / 2; ++r ) // First half
    {
      this->calcNewRing( radius, height, numSegm, sin( Mathf::PI * r * ringIncr ),
        sin( Mathf::PI * ( r * ringIncr - 0.5f ) ), -0.5f );
    }

    for ( r = 0; r < ringsBody; ++r )
    {
      this->calcNewRing( radius, height, numSegm, 1.0f, 0.0f, r * bodyIncr - 0.5f );
    }

    for ( r = subHeight / 2; r < subHeight; ++r ) // Second half
    {
      this->calcNewRing( radius, height, numSegm, sin( Mathf::PI * r * ringIncr ),
        sin( Mathf::PI * ( r * ringIncr - 0.5f ) ), +0.5f );
    }

    for ( unsigned int r = 0; r < ringsTotal - 1; ++r )
    {
      for ( unsigned int s = 0; s < numSegm - 1; ++s )
      {
        indices.push_back( r * numSegm + ( s + 1 ) );
        indices.push_back( r * numSegm + ( s + 0 ) );
        indices.push_back( ( r + 1 ) * numSegm + ( s + 1 ) );

        indices.push_back( ( r + 1 ) * numSegm + ( s + 0 ) );
        indices.push_back( ( r + 1 ) * numSegm + ( s + 1 ) );
        indices.push_back( r * numSegm + s );
      }
    }

    MAXPOINTS = vertices.size( );

  }


  void CapsulePrimitive::calcNewRing( float radius, float height,
    unsigned int segments, float r, float y, float dy )
  {
    float segIncr = 1.0f / ( float ) ( segments - 1 );

    for ( unsigned int s = 0; s < segments; ++s )
    {
      const float val = ( Mathf::PI * 2.0f ) * s * segIncr;
      const float x = cos( val ) * r;
      const float z = sin( val ) * r;

      vertices.push_back( Vector3( radius * x,
        radius * y + height * dy,
        radius * z ) );

      normals.push_back( Vector3( x, y, z ) );

      texCoords.push_back( Vector2( 1.0f - ( s * segIncr ),
        0.5f - ( ( radius * y + height * dy ) /
        ( 2.0f * radius + height ) ) ) );
    }
  }
}