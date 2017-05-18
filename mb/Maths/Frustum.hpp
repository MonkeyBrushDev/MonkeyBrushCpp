#ifndef __MB_FRUSTUM__
#define __MB_FRUSTUM__

#include <math.h>
#include <array>
#include <mb/api.h>

namespace mb
{
  class Frustum
  {
    enum {
      FRUSTUM_UMIN = 2,
      FRUSTUM_UMAX = 3,
      FRUSTUM_RMIN = 0,
      FRUSTUM_RMAX = 1,
      FRUSTUM_DMIN = 4,
      FRUSTUM_DMAX = 5,
    };
  public:
    Frustum( void );
    MB_API
    Frustum( const float& fov/* = 45.0f*/, const float& ar/* = 1.0f*/,
      const float& near/* = 0.1f*/, const float& far/* = 1000.0f*/ );

    Frustum( const Frustum& f )
    {
      std::copy( std::begin( f._data ), std::end( f._data ), std::begin( _data ) );
    }
    bool operator==( const Frustum &f ) const
    {
      return std::equal( _data.begin( ), _data.end( ), f._data.begin( ) );
    }

    bool operator!=( const Frustum& f ) const
    {
      return !(*this == f);
    }

		float getRMin( void ) const { return _data[ FRUSTUM_RMIN ]; }
		float getRMax( void ) const { return _data[ FRUSTUM_RMAX ]; }
		float getUMin( void ) const { return _data[ FRUSTUM_UMIN ]; }
		float getUMax( void ) const { return _data[ FRUSTUM_UMAX ]; }
		float getDMin( void ) const { return _data[ FRUSTUM_DMIN ]; }
		float getDMax( void ) const { return _data[ FRUSTUM_DMAX ]; }

    // TODO: Replace std::array<float, 16> to Matrix4 projMatrix and orthoMatrix
    std::array<float, 16> computeProjMatrix( void ) const
    {
      float left = getRMin( );
      float right = getRMax( );
      float top = getUMax( );
      float bottom = getUMin( );
      float far = getDMax( );
      float near = getDMin( );

      std::array<float, 16> matrix;
      matrix[ 0 ] = 2.0f * near / ( right - left );
      matrix[ 1 ] = 0.0f;
      matrix[ 2 ] = 0.0f;
      matrix[ 3 ] = 0.0f;

      matrix[ 4 ] = 0.0f;
      matrix[ 5 ] = 2.0f * near / ( top - bottom );
      matrix[ 6 ] = 0.0f;
      matrix[ 7 ] = 0.0f;

      matrix[ 8 ] = ( right + left ) / ( right - left );
      matrix[ 9 ] = ( top + bottom ) / ( top - bottom );
      matrix[ 10 ] = -( far + near ) / ( far - near );
      matrix[ 11 ] = -1.0f;

      matrix[ 12 ] = 0.0f;
      matrix[ 13 ] = 0.0f;
      matrix[ 14 ] = -( 2.0f * far * near ) / ( far - near );
      matrix[ 15 ] = 0.0f;

      return matrix;
    }
    std::array<float, 16> computeOthoMatrix( void ) const
    {
      float near = getDMin( );
      float far = getDMax( );
      float fov = getRMax( ) / getUMax( );
      float right = fov;
      float left = -fov;
      float top = 1.0f;
      float bottom = -1.0f;

      std::array<float, 16> matrix;
      matrix[ 0 ] = ( 2.0f / ( right - left ) );
      matrix[ 1 ] = 0.0f;
      matrix[ 2 ] = 0.0f;
      matrix[ 3 ] = -( right + left ) / ( right - left );

      matrix[ 4 ] = 0.0f;
      matrix[ 5 ] = ( 2.0f / ( top - bottom ) );
      matrix[ 6 ] = -( top + bottom ) / ( top - bottom );
      matrix[ 7 ] = 0.0f;

      matrix[ 8 ] = 0.0f;
      matrix[ 9 ] = 0.0f;
      matrix[ 10 ] = ( -2.0f / ( far - near ) );
      matrix[ 11 ] = ( far + near ) / ( far - near );

      matrix[ 12 ] = 0.0f;
      matrix[ 13 ] = 0.0f;
      matrix[ 14 ] = 0.0f;
      matrix[ 15 ] = 1.0f;

      return matrix;
    }
  protected:
    std::array< float, 6 > _data;
  };
}

#endif /* __MB_FRUSTUM__ */
