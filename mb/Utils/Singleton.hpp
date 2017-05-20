#ifndef __MB_SINGLETON_TEMPLATE__
#define __MB_SINGLETON_TEMPLATE__

#include <mb/api.h>

namespace mb
{
	template< class E >
	class Singleton {
	private:
		static E _dummyInstance;
	public:
		static E* getInstance( void )
		{
			static E instance;
			return &instance;
		}
	};
}

#endif /* __MB_SINGLETON_TEMPLATE__ */
