#include "StateMachine.hpp"
#include <iostream>

namespace mb
{
  State::State( StateMachinePtr owner )
  {
    this->owner = owner;
  }
  State::~State( void )
  {
  }

  StateMachine::StateMachine( void )
  {
    currentState = nullptr;
  }

  StateMachine::~StateMachine( void )
  {
  }

  void StateMachine::SwitchState( StatePtr newState )
  {
    if ( currentState != nullptr )
    {
      currentState->exit( );
    }

    currentState = newState;
    if ( newState != nullptr )
    {
      currentState->enter( );
    }
  }

  void StateMachine::update( const float& )
  {
    if ( currentState != nullptr )
    {
      std::cout << "State: " << currentState->description( ) << std::endl;
      currentState->update( );
    }
    //Component::Update( dt );
  }

}