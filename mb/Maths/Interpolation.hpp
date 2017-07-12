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
