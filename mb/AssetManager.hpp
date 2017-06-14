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
