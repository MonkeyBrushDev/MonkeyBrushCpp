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

#include "Interpolation.hpp"

namespace mb
{
  namespace interpolations
  {
    const float linear( const float& p0, const float& p1,
      const float& t )
    {
      return ( p1 - p0 ) * t + p0;
    }
    const float bezier( const float& x1, const float& y1,
      const float& x2, const float& y2, const float& t )
    {
      float f0 = 1.0f - 3.0f * x2 + 3.0f * x1;
      float f1 = 3.0f * x2 - 6.0f * x1;
      float f2 = 3.0f * x1;

      float rt = t;
      for ( unsigned int i = 0; i < 5; ++i )
      {
        float rt2 = rt * rt;
        float rt3 = rt2 * rt;

        float x = f0 * rt3 + f1 * rt2 + f2 * rt;
        float slope = 1.0f / ( 3.0f * f0 * rt2 + 2.0f * f1 * rt + f2 );
        rt -= ( x - t ) * slope;
        rt = std::min( 1.0f, std::max( 0.0f, rt ) );
      }

      // Resolve cubic bezier
      return 3.0f * std::pow( 1.0f - rt, 2.0f ) * rt * y1 +
        3.0f * ( 1.0f - rt ) * std::pow( rt, 2.0f ) * y2 +
        std::pow( rt, 3.0f );
    }
    const float catmullRom( const float& p0, const float& p1,
      const float& p2, const float& p3, const float& t )
    {
      float
        v0 = ( p2 - p0 ) * 0.5f,
        v1 = ( p3 - p1 ) * 0.5f,
        t2 = t * t,
        t3 = t * t2;
      return ( 2.0f * p1 - 2.0f * p2 + v0 + v1 ) * t3 +
        ( -3.0f * p1 + 3.0f * p2 - 2.0f * v0 - v1 ) * t2 + v0 * t + p1;
    }
  }
}