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

  PickingVisitor::~PickingVisitor( )
  {
  }

  void PickingVisitor::traverse( Node* n )
  {
    _results.reset( );

    Visitor::traverse( n );
    _results.sortCandidates( [ &] ( Node* first, Node* second ) -> bool
    {
      // TODO: Sort candidates using distance(_ray, first->worldBound()->center) < distance(_ray, second->worldBound()->center);
      return false;
    } );
  }

  void PickingVisitor::visitNode( Node* n )
  {
    if ( _filter == nullptr || _filter( n ) )
    {
      _results.addCandidate( n );
    }
  }
  void PickingVisitor::visitGroup( Group* group )
  {
    visitNode( group );
    group->forEachNode( [ &] ( Node* n )
    {
      /*if (n-> )*/
      n->accept( *this );
      /*}*/
    } );
  }
}
