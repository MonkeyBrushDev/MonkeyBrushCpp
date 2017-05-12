#ifndef __MB_FILE_NOT_FOUND_EXCEPTION__
#define __MB_FILE_NOT_FOUND_EXCEPTION__

#include <mb/api.h>

#include "Exception.hpp"

namespace mb
{
	class FileNotFoundException: public Exception
	{
	public:
    MB_API
		FileNotFoundException( std::string filePath )
		: Exception( "Cannot find file " + filePath )
		{
		}
	};
}

#endif /* __MB_FILE_NOT_FOUND_EXCEPTION__ */
