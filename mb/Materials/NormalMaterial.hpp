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

#ifndef __MB_NORMALMATERIAL__
#define __MB_NORMALMATERIAL__

#include <mb/api.h>

#include "../Rendering/Material.hpp"

namespace mb
{
  class NormalMaterial : public Material
  {
  public:
    MB_API
    NormalMaterial( bool flat_shading = false, bool double_sided = false );
  };
}

#endif /* __MB_NORMALMATERIAL__ */
