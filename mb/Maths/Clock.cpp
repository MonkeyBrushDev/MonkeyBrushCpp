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

#include "Clock.hpp"

#include <chrono>

namespace mb
{
  Clock::Clock( void )
  {
  	reset( );
  }

  Clock::Clock( float dt )
  {
    reset( );

    _deltaTime = dt;
  }

  Clock::Clock( const Clock &t )
  {
  	_currentTime = t._currentTime;
  	_lastTime = t._lastTime;
  	_deltaTime = t._deltaTime;
    _accumTime = t._accumTime;
  }

  Clock::~Clock( void )
  {
  }

  Clock &Clock::operator=( const Clock &t )
  {
  	_currentTime = t._currentTime;
  	_lastTime = t._lastTime;
  	_deltaTime = t._deltaTime;
    _accumTime = t._accumTime;

  	return *this;
  }

  void Clock::reset( void )
  {
    auto now = std::chrono::high_resolution_clock::now( )
      .time_since_epoch( );

    _currentTime = 0.001 * std::chrono::duration_cast<
      std::chrono::milliseconds >( now ).count( );
    _lastTime = _currentTime;
    _deltaTime = 0;
    _accumTime = 0;
  }

  void Clock::tick( void )
  {
    auto now = std::chrono::high_resolution_clock::now( )
      .time_since_epoch( );

    _currentTime = 0.001 * std::chrono::duration_cast<
      std::chrono::milliseconds >( now ).count( );
    _deltaTime = _currentTime - _lastTime;
    _lastTime = _currentTime;
    _accumTime += _deltaTime;

    onTick( );
  }

  float Clock::currentTime( void ) const
  {
    return _currentTime;
  }
  void Clock::currentTime( float value )
  {
    _currentTime = value;
  }

  float Clock::lastTime( void ) const
  {
    return _lastTime;
  }
  void Clock::lastTime( float value )
  {
    _lastTime = value;
  }

  float Clock::deltaTime( void ) const
  {
    return _deltaTime;
  }
  void Clock::deltaTime( float value )
  {
    _deltaTime = value;
  }

  float Clock::accumTime( void ) const
  {
    return _accumTime;
  }
  void Clock::accumTime( float value )
  {
    _accumTime = value;
  }

  void Clock::setTimeout( Clock::TimeoutCallback const &callback,
    float timeout )
  {
    _timeoutCallback = callback;
    _timeout = timeout;
    _repeat = false;
  }

  void Clock::setInterval( Clock::TimeoutCallback const &callback,
    float timeout )
  {
    _timeoutCallback = callback;
    _timeout = timeout;
    _repeat = true;
  }

  Clock &Clock::operator+=( float deltaTime )
  {
    _deltaTime = deltaTime;
    _accumTime += _deltaTime;
    onTick( );
    return *this;
  }

  Clock &Clock::operator+=( const Clock &other )
  {
    *this += other.deltaTime( );
    return *this;
  }

  void Clock::onTick( void )
  {
  	if ( _timeoutCallback != nullptr )
    {
  		_timeout -= _deltaTime;
  		if ( _timeout <= 0.0 )
      {
  			_timeoutCallback( );
  			if ( !_repeat )
        {
  				_timeoutCallback = nullptr;
  			}
  		}
  	}
  }
}
