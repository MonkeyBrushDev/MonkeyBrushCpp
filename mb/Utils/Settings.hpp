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

#ifndef __MB_SETTINGS__
#define __MB_SETTINGS__

#include <map>

namespace mb
{
  class Settings
  {
  private:
    static std::map< std::string, std::string > _settings;
  public:
    static bool existsKey( const std::string& key );

    template< typename T >
    static void set( const std::string& key, T value )
    {
      std::stringstream str;
      str << value;
      _settings[ key ] = str.str( );
    }

    template< typename T >
    static T get( const std::string& key, T def )
    {
      if ( !existsKey( key ) )
      {
        // key undefined
        return def;
      }

      std::stringstream str;
      str << _settings[ key ];
      T value;
      str >> value;
      return value;
    }
  };
}

namespace mb
{
  std::map< std::string, std::string > Settings::_settings;

  bool Settings::existsKey( const std::string& key )
  {
    return ( _settings.find( key ) != _settings.end( ) );
  }
}

#endif /* __MB_SETTINGS__ */
