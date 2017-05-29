#ifndef __MB_FILE_SYSTEM__
#define __MB_FILE_SYSTEM__

#include "Macros.hpp"

namespace mb
{
  class FileSystem
  {
  public:
    static std::string getBaseDirectory( void ) { return _baseDirectory; }
    static void setBaseDirectory( const std::string& baseDirectory )
    {
      _baseDirectory = baseDirectory;
    }
    static std::string extractDirectory( const std::string& path )
    {
      std::string dir;
#if defined(MB_PLATFORM_WINDOWS)
      dir = path.substr( 0, path.find_last_of( '\\' ) );
#elif defined(MB_PLATFORM_LINUX)
      dir = path.substr( 0, path.find_last_of( '/' ) );
#else
      throw;
#endif
      if ( dir == path ) { return ""; }

      return dir;
    }
    static std::string getPathForResource( const std::string& filePath )
    {
      return getBaseDirectory( ) + std::string( "/" ) + getRelativePath( filePath );
    }
    static std::string getRelativePath( const std::string& absolutePath )
    {
      unsigned int pos = absolutePath.find( _baseDirectory + std::string( "/" ) );
      if ( pos == 0 )
      {
        return absolutePath.substr( _baseDirectory.length() + 1 );
      }

      return absolutePath;
    }
  protected:
    static std::string _baseDirectory;
  };

  std::string FileSystem::_baseDirectory = std::string( "." );
}

#endif /* __MB_FILE_SYSTEM__ */
