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
    _results.sort( [ &] ( Node* n1, Node* n2 ) -> bool
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
