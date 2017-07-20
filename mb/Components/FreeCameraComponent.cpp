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

#include "FreeCameraComponent.hpp"
#include "../Io/Input.hpp"
#include "../Scenegraph/Node.hpp"

namespace mb
{
  void FreeCameraComponent::start( void )
  {
    auto root = node( );
    initPosition = root->local().getPosition( );
    initRotation = root->local().getRotation();
  }
  void FreeCameraComponent::update( const mb::Clock& clock )
  {
    float speed = 1.0f;

    if( mb::Input::isKeyPressed( mb::Keyboard::Key::LShift ) || mb::Input::isKeyPressed( mb::Keyboard::Key::RShift ) )
    {
      speed *= fastMovementSpeed;
    }

    auto root = node( );
    speed *= clock.getDeltaTime( );

    // Code based on https://gist.github.com/ashleydavis/f025c03a9221bc840a2b
    if( mb::Input::isKeyPressed( mb::Keyboard::Key::A ) )
    {
      root->local( ).setPosition( root->local( ).getPosition( ) + ( -root->local( ).getRight( ) * speed ) );
    }
    else if ( mb::Input::isKeyPressed( mb::Keyboard::Key::D ) )
    {
      root->local( ).setPosition( root->local( ).getPosition( ) + ( root->local( ).getRight( ) * speed ) );
    }
    else if( mb::Input::isKeyPressed( mb::Keyboard::Key::W ) )
    {
      root->local( ).setPosition( root->local( ).getPosition( ) + ( root->local( ).getUp( ) * speed ) );
    }
    else if( mb::Input::isKeyPressed( mb::Keyboard::Key::S ) )
    {
      root->local( ).setPosition( root->local( ).getPosition( ) + ( -root->local( ).getUp( ) * speed ) );
    }
    else if( mb::Input::isKeyPressed( mb::Keyboard::Key::Q ) )
    {
      root->local( ).setPosition( root->local( ).getPosition( ) + ( root->local( ).getForward( ) * speed ) );
    }
    else if( mb::Input::isKeyPressed( mb::Keyboard::Key::E ) )
    {
      root->local( ).setPosition( root->local( ).getPosition( ) + ( -root->local( ).getForward( ) * speed ) );
    }
    else if( mb::Input::isKeyPressed( mb::Keyboard::Key::R ) )
    {
      root->local( ).setPosition( root->local( ).getPosition( ) + ( mb::Vector3::UP * speed ) );
    }
    else if( mb::Input::isKeyPressed( mb::Keyboard::Key::F ) )
    {
      root->local( ).setPosition( root->local( ).getPosition( ) + ( -mb::Vector3::UP * speed ) );
    }
    else if( mb::Input::isKeyPressed( mb::Keyboard::Key::Space ) )
    {
      // Reset position
      root->local( ).setPosition( initPosition );
      root->local( ).setRotation( initRotation );
    }


    // TODO: Ugly, dont working good :(
    static float x_rot = 0.0f;
    static float y_rot = 0.0f;
    if ( mb::Input::isKeyPressed( mb::Keyboard::Key::Left ) )
    {
      y_rot -= speed *clock.getDeltaTime( );
      node( )->local( ).rotate( ).fromAxisAngle(
        mb::Vector3::Y_AXIS, y_rot * mb::Mathf::TWO_PI );
    }
    else if ( mb::Input::isKeyPressed( mb::Keyboard::Key::Right ) )
    {
      y_rot += speed *clock.getDeltaTime( );
      node( )->local( ).rotate( ).fromAxisAngle(
        mb::Vector3::Y_AXIS, y_rot * mb::Mathf::TWO_PI );
    }
    else if ( mb::Input::isKeyPressed( mb::Keyboard::Key::Up ) )
    {
      x_rot += speed *clock.getDeltaTime( );
      node( )->local( ).rotate( ).fromAxisAngle(
        mb::Vector3::X_AXIS, x_rot * mb::Mathf::TWO_PI );
    }
    else if ( mb::Input::isKeyPressed( mb::Keyboard::Key::Down ) )
    {
      x_rot -= speed *clock.getDeltaTime( );
      node( )->local( ).rotate( ).fromAxisAngle(
        mb::Vector3::X_AXIS, x_rot * mb::Mathf::TWO_PI );
    }
  }
}
