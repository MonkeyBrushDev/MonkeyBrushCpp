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

#ifndef __MB_PICKING_VISITOR__
#define __MB_PICKING_VISITOR__

#include "Visitor.hpp"
#include <functional>
#include <algorithm>
#include <vector>
#include "../Maths/Ray.hpp"

// TODO: Rewrite this code using FindNodes visitor extension.

namespace mb
{
  class Node;
  class PickingVisitor :
    public Visitor
  {
  private:
    typedef std::function< bool( Node* )> FilterType;
  public:
    class Results
    {
    public:
      void reset( void )
      {
        _candidates.clear( );
      }
      void sort( std::function< bool( Node *, Node * ) > callback )
      {
        std::sort( _candidates.begin( ), _candidates.end( ), callback );
      }
      void push( Node *candidate )
      {
        _candidates.push_back( candidate );
      }
      void forEachCandidate( std::function< void( Node * ) > callback )
      {
        auto cs = _candidates;
        for ( auto c : cs )
        {
          callback( c );
        }
      }
      bool hasResults( void )
      {
        return !_candidates.empty( );
      }
      Node *getBestCandidate( void )
      {
        if ( !hasResults( ) )
        {
          return nullptr;
        }
        return _candidates.front( );
      }
    private:
      std::vector< Node* > _candidates;
    };
    MB_API
    PickingVisitor( const Ray& ray, Results &results, FilterType filter );
    MB_API
    virtual void traverse( Node *node ) override;
    MB_API
    virtual void visitNode( Node *node ) override;
    MB_API
    virtual void visitGroup( Group *node ) override;
  private:
    Ray _ray;
    Results &_results;
    FilterType _filter;
  };
}

#endif /* __MB_PICKING_VISITOR__ */
