#ifndef __MB_EXCEPTION__
#define __MB_EXCEPTION__

#include <mb/api.h>

#include <stdexcept>
#include <string>

namespace mb
{
	class Exception: public std::runtime_error
	{
	public:
    	MB_API
		Exception( std::string message )
		: std::runtime_error( message.c_str( ) )
		{
		}
	};
}

#endif /* __MB_EXCEPTION__ */
