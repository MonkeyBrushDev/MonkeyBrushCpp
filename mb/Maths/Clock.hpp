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

#ifndef __MB_CLOCK__
#define __MB_CLOCK__

#include <functional>
#include <mb/api.h>

namespace mb
{
  class Clock
  {
  public:
    MB_API
    Clock( void );
    MB_API
    explicit Clock( float dt );
    MB_API
    Clock( const Clock &c );
    MB_API
    ~Clock( void );
    MB_API
    Clock &operator=( const Clock &other );

    MB_API
    void reset( void );
    MB_API
    void tick( void );

    MB_API
    float currentTime( void ) const;
    MB_API
    void currentTime( float value );

    MB_API
    float lastTime( void ) const;
    MB_API
    void lastTime( float value );

    MB_API
    float deltaTime( void ) const;
    MB_API
    void deltaTime( float value );

    MB_API
    float accumTime( void ) const;
    MB_API
    void accumTime( float value );

  private:
    float _currentTime;
    float _lastTime;
    float _deltaTime;
    float _accumTime;

  public:
    typedef std::function< void( void ) > TimeoutCallback;
    MB_API
      void setTimeout( TimeoutCallback const &callback,
      float timeout );
    MB_API
      void setInterval( TimeoutCallback const &callback,
      float timeout );

  private:
    TimeoutCallback _timeoutCallback;
    float _timeout;
    bool _repeat;

  public:
    /**
     Ticks the clock by a fixed delta time
     As a side effect, _accumTime gets incremented by the new
     _deltaTime. Callbacks get executed if timeout is over
     */
    MB_API
    Clock &operator+=( float delta );

    /**
     Ticks the clock by another clock's delta time
     As a side effect, _accumTime gets incremented by the new
     _deltaTime. Callbacks get executed if timeout is over
     */
    MB_API
    Clock &operator+=( const Clock &other );

  private:
    void onTick( void );
  };
}

#endif /* __MB_CLOCK__ */
