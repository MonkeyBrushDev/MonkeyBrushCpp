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

#ifndef __MB_BLACKWHITEPPMATERIAL__
#define __MB_BLACKWHITEPPMATERIAL__

#include <mb/api.h>

#include "PostProcessMaterial.hpp"

namespace mb
{
  class BlackWhitePPMaterial: public PostProcessMaterial
  {
  public:
    MB_API
    BlackWhitePPMaterial( void );
  };
}

#endif /* __MB_BLACKWHITEPPMATERIAL__ */
