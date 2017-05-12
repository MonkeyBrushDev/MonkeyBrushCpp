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
