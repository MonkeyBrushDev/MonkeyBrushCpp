#ifndef __MB_RANDOM__
#define __MB_RANDOM__

#include <random>
#include <mb/api.h>

namespace mb
{
  class Random
  {
  public:
    MB_API
    Random( void );
    MB_API
    float nextFloat( float min, float maxExcluding );
    MB_API
    int nextInt( int min, int max );
    MB_API
    float next( void );
    MB_API
    void seed( unsigned int s );
  protected:
    std::random_device rd;
    std::default_random_engine el;
  };
}

#endif /* __MB_RANDOM__ */
