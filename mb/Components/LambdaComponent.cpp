#include "LambdaComponent.hpp"

namespace mb
{
  LambdaComponent::LambdaComponent( LambdaCallback cb )
    : _callback( cb )
  {
  }
  void LambdaComponent::update( const float& dt )
  {
    _callback( node(), dt );
  }
}
