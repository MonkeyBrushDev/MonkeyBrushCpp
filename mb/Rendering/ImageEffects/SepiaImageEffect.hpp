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

#ifndef __MB_SEPIA_EFFECT__
#define __MB_SEPIA_EFFECT__

#include "ImageEffect.hpp"

namespace mb
{
  class Camera;

  class SepiaToneEffect :
    public ImageEffect
  {
  public:
    MB_API
    SepiaToneEffect( void );
    MB_API
    virtual void compute( Renderer*, Camera* camera ) override;
    MB_API
    virtual void apply( Renderer*, Camera* camera ) override;
  protected:
    MaterialPtr _material;
  };
}

#endif /* __MB_SEPIA_EFFECT__ */
