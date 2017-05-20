#ifndef __MB_NONCOPYABLE__
#define __MB_NONCOPYABLE__

#include <mb/api.h>

namespace mb
{
  /**
   * A class derived from this can't be copied or reassigned
   */
	class NonCopyable
	{
	protected:
    NonCopyable( void ) { }
		~NonCopyable( void ) { }
	private:
		NonCopyable( const NonCopyable& ) = delete;
		const NonCopyable& operator=( const NonCopyable& ) = delete;
	};
}

#endif /* __MB_NONCOPYABLE__ */
