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

// Create automatic getter and setter.
#define MB_SYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void) const { return varName; }\
public: virtual void set##funName(varType var){ varName = var; }

// Create automatic setter.
#define MB_SYNTHESIZE_WRITEONLY(varType, varName, funName)\
protected: varType varName;\
public: virtual void set##funName(varType var){ varName = var; }

// Create automatic getter and setter with pass by reference.
#define MB_SYNTHESIZE_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: virtual const varType& get##funName(void) const { return varName; }\
public: virtual void set##funName(const varType& var){ varName = var; }

// Create automatic setter with pass by reference.
#define MB_SYNTHESIZE_WRITEONLY_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: virtual void set##funName(const varType& var){ varName = var; }

// Create automatic getter for readonly.
#define MB_SYNTHESIZE_READONLY(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void) const { return varName; }\

// Create only getter header method.
#define MB_PROPERTY_READONLY(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void) const;

// Create only getter header method with pass by reference.
#define MB_PROPERTY_READONLY_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: virtual const varType& get##funName(void) const;

// Create only getter and setter header.
#define MB_PROPERTY(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void) const;\
public: virtual void set##funName(varType var);

// Create only getter and setter header with pass by reference.
#define MB_PROPERTY_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: virtual const varType& get##funName(void) const;\
public: virtual void set##funName(const varType& var);

#define MB_TO_STR(A) #A

#endif /* __MB_MACROS__ */
