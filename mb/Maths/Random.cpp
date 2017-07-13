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
