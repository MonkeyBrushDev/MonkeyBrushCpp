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

#ifndef __MB_LIGHT__
#define __MB_LIGHT__

#include "Node.hpp"
#include <mb/api.h>

namespace mb
{
  class Light :
    public Node
  {
    enum class ShadowType
    {
      NO_SHADOW,
      SOFT_SHADOW,
      HARD_SHADOW
    };
  public:
    MB_API
    Light( void );
    MB_API
    ~Light( void );

  public:
    MB_API
    virtual void accept( Visitor& v ) override;

  public:
    // TODO: Color4 color;
    ShadowType shadowType;
    float strength = 1.0f;
    float bias = 0.05f;
    float normalBias = 0.4f;
    float nearPlane = 0.2f;
  };
}

#endif /* __MB_LIGHT__ */
