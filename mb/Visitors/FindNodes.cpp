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

#include "FindNodes.hpp"
#include "../Scenegraph/Group.hpp"

#include <algorithm>

namespace mb
{
  FindNodes::FindNodes( FindNodes::NodeSelector sl )
    : _selector( sl )
  {
  }

  void FindNodes::eachMatchNodes( std::function< void( Node * ) > cb )
  {
    std::for_each(
      this->_matches.begin( ),
      this->_matches.end( ),
      cb
      );
  }

  void FindNodes::reset( void )
  {
    _matches.clear( );
    Visitor::reset( );
  }

  void FindNodes::visitNode( Node *node )
  {
    if ( _selector( node ) )
    {
      _matches.push_back( node );
    }
  }

  void FindNodes::visitGroup( Group *group )
  {
    visitNode( group );
    Visitor::visitGroup( group );
  }

}