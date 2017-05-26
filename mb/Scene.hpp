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

#ifndef __MB_SCENE__
#define __MB_SCENE__

#include "Scenegraph/Group.hpp"

#include <mb/api.h>

namespace mb
{
  class Scene
    : public Group
  {
  public:
    MB_API
    Scene( const std::string& name )
      : Group( name )
    {
    }
  };
}

#endif /* __MB_SCENE__ */
