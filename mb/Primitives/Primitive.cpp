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

#include "Primitive.hpp"

namespace mb
{
  Primitive::Primitive( Primitive::Type type, Primitive::TDrawType typeDraw )
    : _type( type )
    , _typeDraw( typeDraw )
  {
  }

  Primitive::Type Primitive::getType( void ) const
  {
    return _type;
  }

  Primitive::TDrawType Primitive::getTypeDraw( void ) const
  {
    return _typeDraw;
  }

  std::vector<Vector3> Primitive::getVertices( void ) const
  {
    return vertices;
  }

  std::vector<short> Primitive::getIndices( void ) const
  {
    return indices;
  }

  std::vector<Vector3> Primitive::getNormals( void ) const
  {
    return normals;
  }

  std::vector<Vector2> Primitive::getTexCoords( void ) const
  {
    return texCoords;
  }

  unsigned int Primitive::getMaxPoints( void ) const
  {
    return MAXPOINTS;
  }

  unsigned int Primitive::getVAO( void ) const
  {
    return VAO;
  }

  void Primitive::setVAO(  unsigned int VAO_ )
  {
    VAO = VAO_;
  }

  void Primitive::render( void )
  {
    //std::cout << "\t-Primitive '" << name << "'" << std::endl;
  }
}
