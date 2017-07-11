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

#ifndef __MB_TOONMATERIAL__
#define __MB_TOONMATERIAL__

#include <mb/api.h>

#include "../Rendering/Material.hpp"

namespace mb
{
  class ToonMaterial: public Material
  {
  public:
    MB_API
    ToonMaterial( void );
    MB_API
    void setLevels( const float &v );
  protected:
    mb::UniformPtr _levels;
  };
}

#endif /* __MB_TOONMATERIAL__ */
