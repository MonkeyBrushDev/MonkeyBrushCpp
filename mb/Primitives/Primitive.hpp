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

#ifndef __MB_PRIMITIVE__
#define __MB_PRIMITIVE__

#include <string>
#include <iostream>
#include <mb/api.h>

#include <vector>
#include "../Maths/Vector2.hpp"
#include "../Maths/Vector3.hpp"

namespace mb
{
  class Primitive
  {
  public:
    enum class Type: short
    {
      POINTS = 0,
      LINES,
      LINE_LOOP,
      LINE_STRIP,
      TRIANGLES,
      TRIANGLE_FAN,
      TRIANGLE_STRIP
    };
    MB_API
    Primitive( Primitive::Type type = Primitive::Type::TRIANGLES );
    MB_API
    Primitive::Type getType( void ) const;
    MB_API
    virtual void render( void );
  protected:
    Primitive::Type _type;


  protected:
    std::vector<Vector3> vertices;
    std::vector<short> indices;
    std::vector<Vector3> normals;
    std::vector<Vector2> texCoords;

    unsigned int VAO;
  };
}

#endif /* __MB_PRIMITIVE__ */
