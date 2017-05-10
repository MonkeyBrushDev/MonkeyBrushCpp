#include "Component.hpp"
#include "../scenegraph/Node.hpp"
#include <string>

namespace mb
{
  Component::Component( )
  {
  }

  Component::~Component( )
  {
    std::cout << "[D] Component" << std::endl;
  }

  Node* Component::node( )
  {
    return _node;
  }

  void Component::setNode( Node* n )
  {
    _node = n;
  }

  void Component::update( const float & )
  {
  }

  void Component::start( void )
  {
    std::cout << "Init " << GetUID( ) << " component" << std::endl;
  }

  void Component::onAttach( void )
  {
    std::cout << "Attached " << this->GetUID( ) << " to node '" << this->node( )->name( ) << "'" << std::endl;
  }

  void Component::onDetach( void )
  {
  }
}
