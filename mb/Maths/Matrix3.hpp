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

#ifndef __MB_MATRIX3__
#define __MB_MATRIX3__

#include <mb/api.h>

#include <array>

namespace mb
{

 class Matrix3
 {
  public:
    MB_API
    Matrix3( void )
    {
      this->_values = { {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
      } };
    }
    MB_API
    Matrix3( const std::array<float, 9>& values )
    {
      this->_values = values;
    }
    float* data( void )
    {
      return _values.data( );
    }

    float operator[]( int i ) const
    {
      return _values[ i ];
    }

    float &operator[]( int i )
    {
      return _values[ i ];
    }
   protected:
    std::array<float, 9> _values;
  };
}

#endif /* __MB_MATRIX3__ */
