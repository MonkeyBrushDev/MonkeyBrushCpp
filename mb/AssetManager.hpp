#ifndef __MB_ASSET_MANAGER__
#define __MB_ASSET_MANAGER__

#include "Rendering/Texture.hpp"

namespace mb
{
  template< class T >
  class AssetManager: public Singleton< AssetManager< T > >
  {
  public:
    AssetManager( void )
    {
    }
    virtual ~AssetManager( void )
    {
    }

    T get( const std::string& name )
    {
      return _assets[ name ];
    }
    void set( const std::string& name, T asset )
    {
      _assets[ name ] = asset;
    }
  protected:
    std::unordered_map< std::string, T > _assets;
  };

  typedef AssetManager< mb::Texture2D* > TextureLibrary;
}

#endif /*__MB_ASSET_MANAGER__*/
