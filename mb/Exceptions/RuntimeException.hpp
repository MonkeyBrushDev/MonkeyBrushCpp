#ifndef __MB_RUNTIME_EXCEPTION__
#define __MB_RUNTIME_EXCEPTION__

#include <mb/api.h>

#include "Exception.hpp"

namespace mb
{
	class RuntimeException: public Exception
	{
	public:
	    MB_API
		RuntimeException( std::string message )
		: Exception( "PROGRAM TERMINATED BECAUSE OF AN ERROR: " + message )
		{
		}
	};
}

#endif /* __MB_RUNTIME_EXCEPTION__ */
