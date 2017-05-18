#ifndef __MB_CUSTOM_PING_PONG__
#define __MB_CUSTOM_PING_PONG__

#include <mb/api.h>

#include <functional>

namespace mb
{
  template <class T>
  class CustomPingPong
  {
  public:
    CustomPingPong( const T & elem1, const T & elem2 );
    void swap( void );
    void swap( std::function<void()> cb );
    T first( void ) const;
    T last( void ) const;
  protected:
    T _elem1;
    T _elem2;
  };
}

#include "CustomPingPong.inl"

#endif /* __MB_CUSTOM_PING_PONG__ */
