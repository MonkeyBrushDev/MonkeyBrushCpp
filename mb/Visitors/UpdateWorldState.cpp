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

#include "UpdateWorldState.hpp"

#include "../Scenegraph/Node.hpp"
#include "../Scenegraph/Group.hpp"

namespace mb
{
  void UpdateWorldState::visitNode( Node *node )
  {
    if ( node->hasParent( ) )
    {
      node->world( ).computeFrom( node->parent( )->getWorld( ), node->getLocal( ) ); // Compute world model of current node from parent
    }
    else
    {
      node->setWorld( node->getLocal( ) ); // World model of current node as local matrix
    }
    // TODO: Compute world bound for current node to contain to himself
  }

  void UpdateWorldState::visitGroup( Group *group )
  {
    visitNode( group );
    Visitor::visitGroup( group );

    if ( group->hasNodes( ) )
    {
      bool first = true;
      group->forEachNode( [&] ( Node* node )
      {
        if ( first )
        {
          first = false;
          // TODO: Compute world bound for current group to contain current node.
        }
        else
        {
          // TODO: Expand world bound for current group to contain current node
          //group->worldBound()->expand( node->getWorldBound( ) );
        }
      } );
    }
  }
}
