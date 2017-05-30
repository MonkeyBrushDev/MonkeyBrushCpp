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
  void FreeCameraComponent::update( const float& dt )
  {
    float speed = 1.0f;

    if( mb::Input::isKeyPressed( mb::Keyboard::Key::LShift ) || mb::Input::isKeyPressed( mb::Keyboard::Key::RShift ) )
    {
      speed *= fastMovementSpeed;
    }

    auto root = node( );
    speed *= dt;

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
  }
}
