#ifndef __MB_MACROS__
#define __MB_MACROS__

#if defined ( __ANDROID__ )
  #define MB_PLATFORM_ANDROID
#elif defined( __APPLE__ )
  #include <TargetConditionals.h>
  #if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
    #define MB_PLATFORM_IOS
  #else
    #define MB_PLATFORM_OSX
  #endif
#elif defined( __MINGW32__ ) || defined( WIN32 ) || defined( __WIN32__ )
  #define MB_PLATFORM_WINDOWS
#else
  #define MB_PLATFORM_LINUX
#endif

#if defined( MB_PLATFORM_WINDOWS ) || defined( MB_PLATFORM_LINUX ) ||defined( MB_PLATFORM_OSX )
  #define MB_PLATFORM_DESKTOP
#endif

#if defined( MB_PLATFORM_IOS ) || defined( MB_PLATFORM_ANDROID )
  #define MB_PLATFORM_MOBILE
#endif

#endif /* __MB_MACROS__ */
