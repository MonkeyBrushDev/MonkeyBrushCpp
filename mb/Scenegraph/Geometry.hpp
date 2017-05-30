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

#ifndef __MB_GEOMETRY__
#define __MB_GEOMETRY__

#include "Node.hpp"
#include "../Primitives/Primitive.hpp"

#include <iostream>
#include <string>

namespace mb
{
  // TODO: Use shared_ptr instead raw pointers
  class Geometry: public Node
  {
  public:
    MB_API
    Geometry( const std::string& name = "Geometry" );
    MB_API
    virtual ~Geometry( void );
    MB_API
    void removeAllPrimitives( void );
    MB_API
    bool hasPrimitives( void ) const;
    MB_API
    void addPrimitive( Primitive* p );
    MB_API
    void removePrimitive( Primitive *p );
    MB_API
    void forEachPrimitive( std::function< void(Primitive* )> cb );
  protected:
    std::vector< Primitive* > _primitives;

  public:
    virtual void accept( Visitor& v ) override;
  };
}

#endif /* __MB_GEOMETRY__ */
