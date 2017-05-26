/**
 * Copyright (c) 2017, Monkey Brush
 * All rights reserved.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

#include "Component.hpp"
#include "../Scenegraph/Node.hpp"
#include <string>

namespace mb
{
  Component::Component( )
    : _enabled( true )
    , _node( nullptr )
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
  bool Component::isEnabled( void ) const
  {
    return _enabled;
  }
  void Component::enable( void )
  {
    setEnabled( true );
  }
  void Component::disable( void )
  {
    setEnabled( false );
  }
  void Component::setEnabled( const bool v )
  {
    _enabled = v;
    if ( _enabled == true )
    {
      onEnable( );
    } else if ( _enabled == false )
    {
      onDisable( );
    }
  }
  void Component::toggle( void )
  {
    setEnabled( !isEnabled( ) );
  }
}
