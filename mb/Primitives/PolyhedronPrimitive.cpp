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

#include "PolyhedronPrimitive.hpp"

#include "../Includes.hpp"

#include <map>

namespace mb
{
  PolyhedronPrimitive::PolyhedronPrimitive( float radius, unsigned int subdivisions,
                                            Primitive::Type type,
                                            Primitive::TDrawType typeDraw )
  : Primitive( type, typeDraw )
  {
    _createPolyhedron( vertices, indices );

    for ( const auto& v : vertices )
    {
      float mod = v.length( );
      
      float nX = v.x( ) / mod;
      float nY = v.y( ) / mod;
      float nZ = v.z( ) / mod;

      normals.push_back( v.getNormalized( ) );
      texCoords.push_back( mb::Vector2( std::atan2( nX, nZ ), std::acos( nY ) ) );
    }

    std::map< std::string, unsigned int > _pointsCache;

    auto midPoint( [ & ] ( unsigned int a, unsigned int b )
    {
      std::string key = indices[ a ] < indices[ b ] ?
        std::to_string( indices[ a ] ) + ":" + std::to_string( indices[ b ] ) :
        std::to_string( indices[ b ] ) + ":" + std::to_string( indices[ a ] );

      std::map<std::string, unsigned int>::iterator r = _pointsCache.find(key);
      if (r != _pointsCache.end())
      {
        return r->second;
      }

      unsigned int index = vertices.size( );
      mb::Vector3 vv = ( vertices[ indices[ a ] * 0.5f ] + vertices[ indices[ b ] ] );

      float mod = vv.length( );

      mb::Vector3 aux = vertices.at( index );
      float nX = aux.x( ) / mod;
      float nY = aux.y( ) / mod;
      float nZ = aux.z( ) / mod;

      normals.push_back( mb::Vector3( nX, nY, nZ ) );

      texCoords.push_back( mb::Vector2( (std::atan2(nX, nZ) / Mathf::PI) * 0.5f, std::acos(nY) / Mathf::PI ) );

      vv *= radius / mod;
      vertices.push_back( vv );

      _pointsCache[ key ] = index;

      return index;
    } );

    // Regenerate indices
    for ( unsigned int ir = 0; ir < subdivisions; ++ir )
    {
      std::vector< short > new_el;
      for ( unsigned int i = 0, size = indices.size( ); i < size; i += 3 )
      {
        unsigned int midA = midPoint( i, i + 1 );
        unsigned int midB = midPoint( i + 1, i + 2 );
        unsigned int midC = midPoint( i + 2, i );
        new_el.push_back( indices[ i ] );
        new_el.push_back( midA );
        new_el.push_back( midC );
        new_el.push_back( indices[ i + 1 ] );
        new_el.push_back( midB );
        new_el.push_back( midA );
        new_el.push_back( indices[ i + 2 ] );
        new_el.push_back( midC );
        new_el.push_back( midB );
        new_el.push_back( midA );
        new_el.push_back( midB );
        new_el.push_back( midC );
      }
      indices = new_el;
    }

  }

  // IcosahedronPrimitive
  IcosahedronPrimitive::IcosahedronPrimitive( void )
    : PolyhedronPrimitive( 1.0f, 1 )
  {
  }
  void IcosahedronPrimitive::_createPolyhedron( std::vector< mb::Vector3 >& verts, std::vector<short>& el )
  {
    float t = ( 1.0f + std::sqrt( 5.0f ) ) / 2.0f;
    verts = {
      mb::Vector3( -1.0f, t, 0.0f ),
      mb::Vector3( 1.0f, t, 0.0f ),
      mb::Vector3( -1.0f, -t, 0.0f ),
      mb::Vector3( 1.0f, -t, 0.0f ),

      mb::Vector3( 0.0f, -1.0f, t ),
      mb::Vector3( 0.0f, 1.0f, t ),
      mb::Vector3( 0.0f, -1.0f, -t ),
      mb::Vector3( 0.0f, 1.0f, -t ),

      mb::Vector3( t, 0.0f, -1.0f ),
      mb::Vector3( t, 0.0f, 1.0f ),
      mb::Vector3( -t, 0.0f, -1.0f ),
      mb::Vector3( -t, 0.0f, 1.0f )
    };
    el = {
      0, 11, 5,
      0, 5, 1,
      0, 1, 7,
      0, 7, 10,
      0, 10, 11,
      1, 5, 9,
      5, 11, 4,
      11, 10, 2,
      10, 7, 6,
      7, 1, 8,
      3, 9, 4,
      3, 4, 2,
      3, 2, 6,
      3, 6, 8,
      3, 8, 9,
      4, 9, 5,
      2, 4, 11,
      6, 2, 10,
      8, 6, 7,
      9, 8, 1
    };
  }
}
