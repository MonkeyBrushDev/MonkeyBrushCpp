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

#ifndef __MB_INTERPOLATION__
#define __MB_INTERPOLATION__

#include <mb/api.h>

#include <cmath>
#include <algorithm>

namespace mb
{
	namespace interpolation
	{
		MB_API
		const float linear( const float& p0, const float& p1, const float& t );
		MB_API
		const float bezier( const float& x1, const float& y1, const float& x2, 
      const float& y2, const float& t );
		MB_API
		const float catmullRom( const float& p0, const float& p1, const float& p2, 
      const float& p3, const float& t );
	};
}

#endif /* __MB_INTERPOLATION__ */
