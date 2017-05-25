#include "mbTests.h"
#include <mb/mb.h>

using namespace mb;

class AttackingState : public State
{
public:
  AttackingState( StateMachinePtr owner_ )
    : State( owner_ )
  {
  }
  virtual void enter( )
  {
    std::cout << "AttackingState Enter" << std::endl;
  }
  virtual void exit( )
  {
    std::cout << "AttackingState Exit" << std::endl;
  }
  virtual void update( )
  {
    std::cout << "AttackingState Update" << std::endl;
  }

  virtual std::string description( )
  {
    return "Attacking";
  }
};

class IdleState : public State
{
public:
  IdleState( StateMachinePtr owner_ )
    : State( owner_ )
  {
  }
  virtual void enter( )
  {
    std::cout << "IdleState Enter" << std::endl;
  }
  virtual void exit( )
  {
    std::cout << "IdleState Exit" << std::endl;
  }
  virtual void update( )
  {
    std::cout << "IdleState Update" << std::endl;
    owner->SwitchState( std::make_shared<AttackingState>( owner ) );
  }

  virtual std::string description( )
  {
    return "Idle";
  }
};

BOOST_AUTO_TEST_CASE( test_state_construction )
{
  // TODO
}