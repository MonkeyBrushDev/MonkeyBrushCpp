#include "LambdaVisitor.hpp"
#include "../Scenegraph/Node.hpp"
#include "../Scenegraph/Group.hpp"

namespace mb
{
  LambdaVisitor::LambdaVisitor( CallbackType cb )
  : _callback(cb )
  {
  }

  LambdaVisitor::~LambdaVisitor( )
  {
  }

  void LambdaVisitor::visitNode( Node* n )
  {
    _callback( n );
  }

  void LambdaVisitor::visitGroup( Group *group )
  {
    _callback( group );
    Visitor::visitGroup( group );
  }
}
