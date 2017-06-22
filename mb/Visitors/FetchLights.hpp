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

#ifndef __MB_FETCH_LIGHTS__
#define __MB_FETCH_LIGHTS__

#include "Visitor.hpp"
#include <vector>
#include <functional>

#include <mb/api.h>

namespace mb
{
  class FetchLights :
    public Visitor
  {
  public:
    virtual void reset( void ) override;
    MB_API
    virtual void visitLight( Light* c ) override;
    MB_API
    bool hasLights( void ) const
    {
      return !_lights.empty( );
    }
    MB_API
    std::vector<Light*> lights( ) const
    {
      return _lights;
    }
    MB_API
    void forEachLight( std::function<void( Light* )> cb );
  protected:
    std::vector<Light*> _lights;
  };
}

#endif /* __MB_FETCH_LIGHTS__ */
