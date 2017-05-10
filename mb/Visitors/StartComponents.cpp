#include "StartComponents.hpp"
#include "../Scenegraph/Node.hpp"

namespace mb
{
  StartComponents::StartComponents( )
  : LambdaVisitor( [] ( Node*n ){ n->startComponents( ); } )
  {
  }

  StartComponents::~StartComponents( )
  {
  }
}
