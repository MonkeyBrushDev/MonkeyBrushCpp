#include "Random.hpp"

namespace mb
{
  Random::Random( void )
    : el( rd( ) )
  {
  }
  float Random::nextFloat( float min, float maxExcluding )
  {
    float r = next( );
    while( r == 1.0f )
    {
      r = next( );
    }
    return r * ( maxExcluding - min ) + min;
  }
  int Random::nextInt( int min, int max )
  {
    return ( int ) floor( nextFloat( min, max ) );
  }
  float Random::next( )
  {
    return std::generate_canonical< float, 32 >( el );
  }
  void Random::seed( unsigned int s )
  {
    el.seed( s );
  }
}
