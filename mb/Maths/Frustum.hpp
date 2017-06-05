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

#ifndef __MB_FRUSTUM__
#define __MB_FRUSTUM__

// TODO: CHECK https://sites.google.com/site/letsmakeavoxelengine/home/frustum-culling

#include <math.h>
#include <array>
#include <mb/api.h>

#include "Matrix4.hpp"

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
    Frustum( const float& fov, const float& ar,
      const float& near, const float& far );

    Frustum( const Frustum& f )
    {
      std::copy( std::begin( f._data ),
        std::end( f._data ), std::begin( _data ) );
    }
    bool operator==( const Frustum &f ) const
    {
      return std::equal( _data.begin( ), _data.end( ), f._data.begin( ) );
    }

    bool operator!=( const Frustum& f ) const
    {
      return !(*this == f);
    }

    MB_API
    float getFOV( void ) const
    {
      return getUMax() / getDMin();
    }
    MB_API
    float getAspect( void ) const
    {
      return getRMax() / getUMax();
    }
    MB_API
    float getLinearDepth( void ) const
    {
      return getDMax() - getDMin();
    }

    /*MB_API
    void setFieldOfView( float fov )
    {
      _data[ FRUSTUM_UMAX ] = near * std::tan( 0.5f * fov * 3.1415f / 180.0f );
    }*/

		float getRMin( void ) const { return _data[ FRUSTUM_RMIN ]; }
		float getRMax( void ) const { return _data[ FRUSTUM_RMAX ]; }
		float getUMin( void ) const { return _data[ FRUSTUM_UMIN ]; }
		float getUMax( void ) const { return _data[ FRUSTUM_UMAX ]; }
		float getDMin( void ) const { return _data[ FRUSTUM_DMIN ]; }
		float getDMax( void ) const { return _data[ FRUSTUM_DMAX ]; }

    Matrix4 computeProjMatrix( void ) const;
    Matrix4 computeOthoMatrix( void ) const;


    friend std::ostream& operator<<( std::ostream &out, const Frustum& f )
    {
      out << std::setiosflags( std::ios::fixed | std::ios::showpoint  )
      << std::setprecision( 4 )
      << "[D = (" << f.getDMin( ) << ", " << f.getDMax( ) << "), "
      << "R = (" << f.getRMin( ) << ", " << f.getRMax( ) << "), "
      << "U = (" << f.getUMin( ) << ", " << f.getUMax( ) << ")]";
      return out;
    }
  protected:
    std::array< float, 6 > _data;
  };
}

#endif /* __MB_FRUSTUM__ */
