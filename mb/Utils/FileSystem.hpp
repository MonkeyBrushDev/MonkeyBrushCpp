/**
 * Copyright (c) 2017, Monkey Brush
 * All rights reserved.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

#ifndef __MB_FILE_SYSTEM__
#define __MB_FILE_SYSTEM__

#include "Macros.hpp"
#include "Singleton.hpp"
#include <string>

namespace mb
{
  class FileSystem: public Singleton<FileSystem>
  {
  public:
    MB_API
    FileSystem( void )
    {
      _baseDirectory = std::string( "." );
    }
    MB_API
    std::string getBaseDirectory( void )
    {
      return _baseDirectory;
    }
    MB_API
    void setBaseDirectory( const std::string& baseDirectory )
    {
      _baseDirectory = baseDirectory;
    }
    MB_API
    std::string extractDirectory( const std::string& path )
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
    std::string getPathForResource( const std::string& filePath )
    {
      return getBaseDirectory( ) + std::string( "/" ) + getRelativePath( filePath );
    }
    std::string getRelativePath( const std::string& absolutePath )
    {
      unsigned int pos = absolutePath.find( _baseDirectory + std::string( "/" ) );
      if ( pos == 0 )
      {
        return absolutePath.substr( _baseDirectory.length() + 1 );
      }

      return absolutePath;
    }
  protected:
    std::string _baseDirectory;
  };
}

#endif /* __MB_FILE_SYSTEM__ */
