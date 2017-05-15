#ifndef __MB__LAYER__
#define __MB__LAYER__

#include <mb/api.h>

#include <array>

namespace mb
{
  class LayerLookup
  {
  public:
    MB_API
    static std::string name( const int& channel );
    MB_API
    static void name( const std::string name, const int& index );
    MB_API
    static int nameToID( const std::string& layer );
  protected:
    static std::array<std::string, 32> _names;
    static bool _initialized;

    static void initialize( );
  };
  class Layer
  {
  public:
    MB_API
    Layer( );
    MB_API
    void set( const int& channel );
    MB_API
    void set( const std::string& layer );
    MB_API
    void enable( const int& channel );
    MB_API
    void enable( const std::string& layer );
    MB_API
    void toggle( const int& channel );
    MB_API
    void toggle( const std::string& layer );
    MB_API
    void disable( const int& channel );
    MB_API
    void disable( const std::string& layer );
    MB_API
    bool check( const Layer& layer2 ) const;
    MB_API
    bool check( const int& channel ) const;
    MB_API
    bool check( const std::string& layer ) const;
  protected:
    int _mask;
  private:
    static int layerNameToID( const std::string& layer );
  };
}

#endif
