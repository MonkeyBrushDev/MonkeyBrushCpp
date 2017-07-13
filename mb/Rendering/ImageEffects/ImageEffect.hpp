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

#ifndef __MB_IMAGE_EFFECT__
#define __MB_IMAGE_EFFECT__

#include <mb/api.h>
#include <memory>
#include "../Material.hpp"

namespace mb
{
  class Camera;
  class Renderer;
  class ImageEffect
  {
  public:

    MB_API
    virtual ~ImageEffect( void ){}

    MB_API
    // TODO Renderer?
    virtual void apply( Renderer* r, Camera* camera ) = 0;
    MB_API
    // TODO Renderer?
    virtual void compute( Renderer* r, Camera* camera ) = 0;

    bool enabled = true;
  protected:
    virtual void renderScreen( Renderer*, MaterialPtr m );
  };
  typedef std::shared_ptr< ImageEffect > ImageEffectPtr;
}

#endif /* __MB_IMAGE_EFFECT__ */
