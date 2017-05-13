#ifndef __MB_NONCOPYABLE__
#define __MB_NONCOPYABLE__

#include <mb/api.h>

namespace mb
{
	class NonCopyable
	{
	protected:
		NonCopyable() {}
		~NonCopyable() {}
	private:
		NonCopyable( const NonCopyable& ) = delete;
		const NonCopyable& operator=( const NonCopyable& ) = delete;
	};
}

#endif /* __MB_NONCOPYABLE__ */
