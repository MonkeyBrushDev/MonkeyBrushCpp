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

#ifndef __MB_RECT__
#define __MB_RECT__

#include <mb/api.h>
#include <algorithm>
#include "Vector2.hpp"

namespace mb
{
  template< typename T >
  class Rect
  {
  public:
    MB_API
    Rect( T x, T y, T w, T h )
    {
      _data[ 0 ] = x;
      _data[ 1 ] = y;
      _data[ 2 ] = w;
      _data[ 3 ] = h;
    }
    MB_API
    Rect( const Rect& r )
    {
      *this = r;
    }
    Rect& operator=( const Rect& r )
    {
      std::copy( std::begin( r._data ), std::end( r._data ), std::begin( _data ) );
      return *this;
    }
    T x( void ) const
    {
      return _data[ 0 ];
    }
    T y( void ) const
    {
      return _data[ 1 ];
    }
    T width( void ) const
    {
      return _data[ 2 ];
    }
    T height( void ) const
    {
      return _data[ 3 ];
    }
    void x( const T& v )
    {
      _data[ 0 ] = v;
    }
    void y( const T& v )
    {
      _data[ 1 ] = v;
    }
    void width( const T& v )
    {
      _data[ 2 ] = v;
    }
    void height( const T& v )
    {
      _data[ 3 ] = v;
    }
    Vector2 getPosition( void ) const
    {
      return Vector2( this._data[ 0 ], this._data[ 1 ] );
    }
    Vector2 getCenter( void ) const
    {
      return Vector2( x( ) + width( ) / 2.0f, y( ) + height( ) / 2.0f );
    }
    void setCenter( const Vector2& center )
    {
      x( center.x( ) - width( ) / 2.0f );
      y( center.y( ) - height( ) / 2.0f );
    }
  protected:
    std::array< T, 4 > _data;
  };
  typedef Rect< int > Recti;
  typedef Rect< float > Rectf;
  typedef Rectf Viewport;
}

#endif /* __MB_RECT__ */
