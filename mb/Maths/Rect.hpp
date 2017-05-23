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
