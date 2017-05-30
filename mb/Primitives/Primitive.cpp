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
  Primitive::Primitive( Primitive::Type type )
    : _type( type )
  {
  }
  Primitive::Type Primitive::getType( void ) const
  {
    return _type;
  }
  void Primitive::setupRender( void )
  {
    //TODO: binds buffers
  }
  void Primitive::render( void )
  {
    //std::cout << "\t-Primitive '" << name << "'" << std::endl;
  }
}
