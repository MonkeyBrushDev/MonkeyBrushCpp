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