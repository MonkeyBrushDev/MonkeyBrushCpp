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

#ifndef __MB_POLYHEDRON_PRIMITIVE__
#define __MB_POLYHEDRON_PRIMITIVE__

#include "Primitive.hpp"

namespace mb
{
  class PolyhedronPrimitive: public Primitive
  {
  public:
    MB_API
    PolyhedronPrimitive( float radius, unsigned int subdivisions ,
                         Primitive::Type type = Primitive::Type::TRIANGLES,
                         Primitive::TDrawType typeDraw = Primitive::DRAW_ELEMENTS );
  protected:
    virtual void _createPolyhedron( std::vector< mb::Vector3 >& verts,
      std::vector<short>& el )
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
  };

  class IcosahedronPrimitive : public PolyhedronPrimitive
  {
  public:
    MB_API
    IcosahedronPrimitive( void );
  protected:
    virtual void _createPolyhedron( std::vector< mb::Vector3 >& verts,
      std::vector<short>& el );
  };
}

#endif /* __MB_POLYHEDRON_PRIMITIVE__ */
