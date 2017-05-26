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
