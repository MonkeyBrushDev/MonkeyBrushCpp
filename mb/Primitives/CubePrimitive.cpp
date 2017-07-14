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

#include "CubePrimitive.hpp"

#include "../Includes.hpp"

namespace mb
{
  CubePrimitive::CubePrimitive(float side , Type type, TDrawType typeDraw)
  : Primitive( type, typeDraw )
  {
    float side2 = side / 2.0f;

  // Vertices
  vertices = std::vector<Vector3> {
    // Front
    Vector3( -side2, -side2, side2 ),
    Vector3( side2, -side2, side2 ),
    Vector3( side2,  side2, side2 ),
    Vector3( -side2,  side2, side2 ),
    // Right
    Vector3( side2, -side2, side2 ),
    Vector3( side2, -side2, -side2 ),
    Vector3( side2,  side2, -side2 ),
    Vector3( side2,  side2, side2 ),
    // Back
    Vector3( -side2, -side2, -side2 ),
    Vector3( -side2,  side2, -side2 ),
    Vector3( side2,  side2, -side2 ),
    Vector3( side2, -side2, -side2 ),
    // Left
    Vector3( -side2, -side2, side2 ),
    Vector3( -side2,  side2, side2 ),
    Vector3( -side2,  side2, -side2 ),
    Vector3( -side2, -side2, -side2 ),
    // Bottom
    Vector3( -side2, -side2, side2 ),
    Vector3( -side2, -side2, -side2 ),
    Vector3( side2, -side2, -side2 ),
    Vector3( side2, -side2, side2 ),
    // Top
    Vector3( -side2,  side2, side2 ),
    Vector3( side2,  side2, side2 ),
    Vector3( side2,  side2, -side2 ),
    Vector3( -side2,  side2, -side2 )
  };

  MAXPOINTS = vertices.size();

  // Normals
  normals = std::vector<Vector3> {
    // Front
    Vector3( 0.0, 0.0, 1.0 ),
    Vector3( 0.0, 0.0, 1.0 ),
    Vector3( 0.0, 0.0, 1.0 ),
    Vector3( 0.0, 0.0, 1.0 ),
    // Right
    Vector3( 1.0, 0.0, 0.0 ),
    Vector3( 1.0, 0.0, 0.0 ),
    Vector3( 1.0, 0.0, 0.0 ),
    Vector3( 1.0, 0.0, 0.0 ),
    // Back
    Vector3( 0.0, 0.0, -1.0 ),
    Vector3( 0.0, 0.0, -1.0 ),
    Vector3( 0.0, 0.0, -1.0 ),
    Vector3( 0.0, 0.0, -1.0 ),
    // Left
    Vector3( -1.0, 0.0, 0.0 ),
    Vector3( -1.0, 0.0, 0.0 ),
    Vector3( -1.0, 0.0, 0.0 ),
    Vector3( -1.0, 0.0, 0.0 ),
    // Bottom
    Vector3( 0.0, -1.0, 0.0 ),
    Vector3( 0.0, -1.0, 0.0 ),
    Vector3( 0.0, -1.0, 0.0 ),
    Vector3( 0.0, -1.0, 0.0 ),
    // Top
    Vector3( 0.0, 1.0, 0.0 ),
    Vector3( 0.0, 1.0, 0.0 ),
    Vector3( 0.0, 1.0, 0.0 ),
    Vector3( 0.0, 1.0, 0.0 )
  };
  // TexCoords
  texCoords = std::vector<Vector2> {
    // Front
    Vector2( 0.0, 0.0 ),
    Vector2( 1.0, 0.0 ),
    Vector2( 1.0, 1.0 ),
    Vector2( 0.0, 1.0 ),
    // Right
    Vector2( 0.0, 0.0 ),
    Vector2( 1.0, 0.0 ),
    Vector2( 1.0, 1.0 ),
    Vector2( 0.0, 1.0 ),
    // Back
    Vector2( 0.0, 0.0 ),
    Vector2( 1.0, 0.0 ),
    Vector2( 1.0, 1.0 ),
    Vector2( 0.0, 1.0 ),
    // Left
    Vector2( 0.0, 0.0 ),
    Vector2( 1.0, 0.0 ),
    Vector2( 1.0, 1.0 ),
    Vector2( 0.0, 1.0 ),
    // Bottom
    Vector2( 0.0, 0.0 ),
    Vector2( 1.0, 0.0 ),
    Vector2( 1.0, 1.0 ),
    Vector2( 0.0, 1.0 ),
    // Top
    Vector2( 0.0, 0.0 ),
    Vector2( 1.0, 0.0 ),
    Vector2( 1.0, 1.0 ),
    Vector2( 0.0, 1.0 )
  };
  // Indices
  indices = std::vector< short > {
    0, 1, 2, 0, 2, 3,
    4, 5, 6, 4, 6, 7,
    8, 9, 10, 8, 10, 11,
    12, 13, 14, 12, 14, 15,
    16, 17, 18, 16, 18, 19,
    20, 21, 22, 20, 22, 23
  };

  }
}
