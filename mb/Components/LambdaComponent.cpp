#include "LambdaComponent.hpp"

namespace mb
{
  LambdaComponent::LambdaComponent( LambdaCallback cb )
    : _callback( cb )
  {
  }
  void update( const float& dt )
  {
    _callback( node(), dt );
  }
}
