#ifndef __MB_SYSTEM__
#define __MB_SYSTEM__

#include <string>

namespace mb
{
  class System
  {
  public:
    System( const std::string& name );
    virtual bool start( );
    virtual void stop( );
    std::string name( ) const
    {
      return _name;
    }
  protected:
    std::string _name;
  };
}

#endif /* __MB_SYSTEM__ */
