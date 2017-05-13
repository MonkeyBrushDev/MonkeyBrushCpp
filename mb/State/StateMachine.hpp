#ifndef __MB_STATE_MACHINE__
#define __MB_STATE_MACHINE__

#include <mb/api.h>
#include <memory>
#include <string>

#include "../Components/Component.hpp"

namespace mb
{
  class StateMachine;
  typedef std::shared_ptr<StateMachine> StateMachinePtr;
  class State
  {
  public:
    State( StateMachinePtr owner );
    ~State( void );
    virtual void enter( ) = 0;
    virtual void exit( ) = 0;
    virtual void update( ) = 0;
    virtual std::string description( ) = 0;
    StateMachinePtr owner;
  };
  typedef std::shared_ptr<State> StatePtr;
  class StateMachine: public Component
  {
    IMPLEMENT_COMPONENT( StateMachine )
  public:
    StateMachine( void );
    ~StateMachine( void );

    StatePtr currentState;

    virtual void update( const float& );
    void SwitchState( StatePtr newState );
  };
}

#endif /* __MB_STATE_MACHINE__ */