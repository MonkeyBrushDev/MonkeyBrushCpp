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

#ifndef __MB_RENDER_SYSTEM__
#define __MB_RENDER_SYSTEM__

#include "System.hpp"

namespace mb
{
  class RenderSystem: public System
  {
  public:
    RenderSystem( void );
    virtual bool start( void ) override;
    virtual void stop( void ) override;
  };
}

#endif /* __MB_RENDER_SYSTEM__ */
