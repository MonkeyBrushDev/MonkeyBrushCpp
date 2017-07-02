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

#ifndef __MB_DEBUG_RENDER_VISITOR__
#define __MB_DEBUG_RENDER_VISITOR__

#include "LambdaVisitor.hpp"
#include <mb/api.h>

#include "../Maths/Clock.hpp"

#include "../Rendering/Renderer.hpp"
#include "../Scenegraph/Camera.hpp"

namespace mb
{
  class DebugRenderVisitor :
    public LambdaVisitor
  {
  public:
    MB_API
    DebugRenderVisitor( Renderer* r, Camera* c );
  };
}

#endif /* __MB_DEBUG_RENDER_VISITOR__ */
