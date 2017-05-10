#include "System.hpp"
#include <iostream>

namespace mb
{
  System::System( const std::string& name )
    : _name( name )
  {
  }

  bool System::start( )
  {
    std::cout << "Starting " << _name << std::endl;
    return true;
  }

  void System::stop( )
  {
    std::cout << "Stop " << _name << std::endl;
  }
}
