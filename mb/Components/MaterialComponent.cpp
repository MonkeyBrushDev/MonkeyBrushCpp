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

#include "MaterialComponent.hpp"
#include <algorithm>

namespace mb
{
  MaterialComponent::~MaterialComponent( void )
  {
    removeMaterials( );
  }
  void MaterialComponent::addMaterial( mb::MaterialPtr  material )
  {
    _materials.push_back( material );
  }
  void MaterialComponent::removeMaterials( void )
  {
    _materials.clear( );
  }
  void MaterialComponent::forEachMaterial( std::function< void ( mb::MaterialPtr ) > cb )
  {
    std::for_each( _materials.begin( ), _materials.end( ), [&] ( MaterialPtr m )
    {
      cb ( m );
    } );
  }
}
