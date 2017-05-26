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

#ifndef __MB_OS__
#define __MB_OS__

#include <mb/api.h>
#include <fstream>

#include "../Utils/Macros.hpp"

#if defined(MB_PLATFORM_WINDOWS)
  #include <direct.h>
#else
  #include <sys/stat.h>
#endif

namespace mb
{
  class os
  {
  public:
    MB_API
    static std::string readFile( const std::string& path )
    {
      std::ifstream file(path);
      std::stringstream buffer;
      buffer << file.rdbuf();
      return buffer.str();
    }
    MB_API
    static void mkdir( const std::string& path )
    {
#if defined(MB_PLATFORM_WINDOWS)
      _mkdir( path.c_str( ) );
#else
      mkdir( path.c_str( ) );
#endif
    }
    MB_API
    static char path_delimiter( void )
    {
      char delimeter;
#if defined(MB_PLATFORM_WINDOWS)
      delimeter = '\\';
#else
      delimeter = '/';
#endif
      return delimeter;
    }
    MB_API
    static std::string path( const std::string& path )
    {
      std::string aux = path;
#if defined(MB_PLATFORM_WINDOWS)
      strReplaceAll( aux, "/", "\\" );
#else
      strReplaceAll( aux, "\\", "/" );
#endif
      return aux;
    }
  private:
    static void strReplaceAll( std::string& source, std::string const& find, 
      std::string const& replace )
    {
      for ( std::string::size_type i = 0; ( i = source.find( find, i ) ) 
        != std::string::npos; )
      {
        source.replace( i, find.length( ), replace );
        i += replace.length( );
      }
    }
  };
}

#endif /* __MB_OS__ */
