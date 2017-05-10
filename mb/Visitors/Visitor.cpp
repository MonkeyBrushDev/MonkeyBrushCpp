#include "Visitor.hpp"

#include "../Scenegraph/Node.hpp"
#include "../Scenegraph/Geometry.hpp"
#include "../Scenegraph/Group.hpp"
#include "../Scenegraph/Camera.hpp"
#include "../Scenegraph/Light.hpp"

namespace mb
{
  Visitor::~Visitor( )
  {
  }

  Visitor::Visitor( const Visitor& )
  {
  }

  Visitor &Visitor::operator= ( const Visitor& )
  {
    return *this;
  }

  void Visitor::reset( void )
  {
  }

  void Visitor::traverse( Node *n )
  {
    reset( );
    n->accept( *this );
  }

  void Visitor::visitNode( Node *node )
  {
    // do nothing
  }

  void Visitor::visitGroup( Group* group )
  {
    group->forEachNode( [&] ( Node* n ) {
      n->accept( *this );
    } );
  }

  void Visitor::visitCamera( Camera *camera )
  {
    visitNode( camera );
  }

  void Visitor::visitLight( Light* light )
  {
    visitNode( light );
  }

  void Visitor::visitGeometry( Geometry *geometry )
  {
    visitNode( geometry );
  }
}
