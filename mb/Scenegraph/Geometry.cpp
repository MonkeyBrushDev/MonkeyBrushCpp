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

#include "Geometry.hpp"
#include <algorithm>

namespace mb
{
  Geometry::Geometry( const std::string& name )
    : Node( name )
  {
    addComponent( new MeshRenderer( 1 ) );
  }
  Geometry::~Geometry( void )
  {
    removeAllPrimitives( );
  }
  void Geometry::removeAllPrimitives( void )
  {
    _primitives.clear( );
  }
  bool Geometry::hasPrimitives( void ) const
  {
    return !_primitives.empty( );
  }
  void Geometry::addPrimitive( Primitive* p )
  {
    _primitives.push_back( p );
  }
  void Geometry::removePrimitive( Primitive *p )
  {
    _primitives.erase( std::find( _primitives.begin( ), _primitives.end( ), p ) );
  }
  void Geometry::accept( Visitor& v )
  {
    v.visitGeometry( this );
  }

  void Geometry::forEachPrimitive( std::function<void(Primitive*)> cb )
  {
    std::for_each( _primitives.begin( ), _primitives.end( ), cb );
  }
}
