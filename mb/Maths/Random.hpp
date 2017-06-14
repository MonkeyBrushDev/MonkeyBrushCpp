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
