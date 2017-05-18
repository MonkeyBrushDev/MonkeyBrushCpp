#ifndef __MB_PARAMS__
#define __MB_PARAMS__

#include <map>

namespace mb
{
    class Params
    {
    private:
      static std::map< std::string, std::string > values;
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
  std::map< std::string, std::string > Params::values;

  bool Params::existsKey( const std::string& key )
  {
    return ( values.find( key ) != values.end( ) );
  }
}

#endif /* __MB_PARAMS__ */
