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

#ifndef __MB_MATERIAL_COMPONENT__
#define __MB_MATERIAL_COMPONENT__

#include "Component.hpp"
#include <mb/api.h>
#include <vector>
#include <functional>
#include "../Rendering/Material.hpp"

namespace mb
{
  // TODO: void removeMaterial( const unsigned int& idx );
  // TODO: void removeMaterial( const Material* material );
  class MaterialComponent : public Component
  {
    IMPLEMENT_COMPONENT( MaterialComponent )
  public:
    MB_API
    virtual ~MaterialComponent( );
    MB_API
    bool hasMaterials( void ) const { return !_materials.empty( ); }
    MB_API
    void addMaterial( MaterialPtr material );
    MB_API
    void removeMaterials( void );
    MB_API
    void forEachMaterial( std::function< void( mb::MaterialPtr ) > callback );
    MB_API
    mb::MaterialPtr first( void )
    {
      return _materials.at( 0 );
    }
  private:
    std::vector< mb::MaterialPtr > _materials;
  };
}

#endif /* __MB_MATERIAL_COMPONENT__ */
