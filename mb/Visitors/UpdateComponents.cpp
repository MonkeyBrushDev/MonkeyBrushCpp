#include "UpdateComponents.hpp"
#include "../Scenegraph/Node.hpp"

namespace mb
{
  UpdateComponents::UpdateComponents( const float& dt )
  : LambdaVisitor( [ dt ] ( Node*n ) { n->updateComponents( dt ); } )
  {
  }

  UpdateComponents::~UpdateComponents( )
  {
  }
}
