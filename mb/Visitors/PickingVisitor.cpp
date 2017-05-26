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

#include "PickingVisitor.hpp"
#include "../Scenegraph/Node.hpp"
#include "../Scenegraph/Group.hpp"

namespace mb
{
  PickingVisitor::PickingVisitor( const Ray& ray,
    Results &results, FilterType filter )
    : _ray( ray )
    , _results( results)
    , _filter( filter )
  {
  }
  
  void PickingVisitor::traverse( Node* n )
  {
    _results.reset( );

    Visitor::traverse( n );
    _results.sort( [ &] ( Node*, Node* ) -> bool
    {
      // TODO: Sort candidates using distance(_ray, n1->worldBound()->center) < distance(_ray, n2->worldBound()->center);
      return false;
      // TODO: return distance_ray_bound( _ray, n1->getWorldBound( )->getCenter( ) ) <
      //  distance_ray_bound( _ray, n2->getWorldBound( )->getCenter( ) );
    } );
  }

  void PickingVisitor::visitNode( Node* n )
  {
    if ( _filter == nullptr || _filter( n ) )
    {
      _results.push( n );
    }
  }
  void PickingVisitor::visitGroup( Group* group )
  {
    visitNode( group );
    group->forEachNode( [ &] ( Node* n )
    {
      if ( _ray.intersect( n->getWorldBound( ) ) )
      {
        n->accept( *this );
      }
    } );
  }
}
