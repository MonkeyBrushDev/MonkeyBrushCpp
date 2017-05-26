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

#ifndef __MB_HAS_PARENT_EXCEPTION__
#define __MB_HAS_PARENT_EXCEPTION__

#include <mb/api.h>

#include "Exception.hpp"

namespace mb
{
	class HasParentException: public Exception
	{
	public:
	    MB_API
		HasParentException( std::string childName,
			std::string parentName, std::string targetName )
			: Exception( "Cannot attach node (\"" + childName +
				"\") to (\"" + targetName +
				"\") because it already has a parent (\"" +
				parentName + "\")" )
		{
		}
	};
}

#endif /* __MB_HAS_PARENT_EXCEPTION__ */
