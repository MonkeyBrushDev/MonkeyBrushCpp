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

#ifndef __MB_TONEMAPPINGMATERIAL__
#define __MB_TONEMAPPINGMATERIAL__

#include <mb/api.h>

#include "PostProcessMaterial.hpp"

namespace mb
{
  class ToneMappingMaterial: public PostProcessMaterial
  {
  public:
    enum class TonemappingOperator: short
    {
      Hable,
      Reinhard,
      HejiDawson,
      Photographic,
    };
    MB_API
    ToneMappingMaterial( TonemappingOperator op );
  };
}

#endif /* __MB_TONEMAPPINGMATERIAL__ */
