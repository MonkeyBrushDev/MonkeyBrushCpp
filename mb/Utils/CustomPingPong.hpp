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
