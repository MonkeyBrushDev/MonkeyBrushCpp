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
