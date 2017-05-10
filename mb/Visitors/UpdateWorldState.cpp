#include "UpdateWorldState.hpp"

#include "../Scenegraph/Node.hpp"
#include "../Scenegraph/Group.hpp"

namespace mb
{
  UpdateWorldState::UpdateWorldState( )
  {
  }

  UpdateWorldState::~UpdateWorldState( )
  {
  }

  void UpdateWorldState::visitNode( Node *node )
  {
    if ( node->hasParent( ) )
    {
      std::cout << "Compute world model (" << node->name( ) << ") from parent ("
        << node->parent( )->name( ) << ")" << std::endl;
      node->world( ).computeFrom( node->parent( )->getWorld( ), node->getLocal( ) );
    }
    else
    {
      std::cout << "World model (" << node->name( ) << ") as local matrix"
        << std::endl;
      node->setWorld( node->getLocal( ) );
    }
    std::cout << "Compute world bound for (" << node->name( ) <<
      ") to contain to himself" << std::endl;
  }

  void UpdateWorldState::visitGroup( Group *group )
  {
    visitNode( group );
    Visitor::visitGroup( group );

    if ( group->hasNodes( ) )
    {
      bool first = true;
      std::string tabs = "\t";
      group->forEachNode( [&] ( Node *node )
      {
        if ( first )
        {
          first = false;
          std::cout << tabs << "Compute world bound for (" << group->name( ) <<
            ") to contain '" << node->name( ) << "'" << std::endl;
        }
        else
        {
          std::cout << tabs << "Expand world bound for (" << group->name( ) <<
            ") to contain '" << node->name( ) << "'" << std::endl;
        }
        tabs += "\t";
      } );
    }
  }
}
