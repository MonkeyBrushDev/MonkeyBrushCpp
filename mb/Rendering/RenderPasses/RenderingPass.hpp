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

#ifndef __MB_RENDERING_PASS__
#define __MB_RENDERING_PASS__

#include <vector>
#include "../BatchQueue.hpp"
#include "../ImageEffects/ImageEffect.hpp"

namespace mb
{
  class Camera;
  class Renderer;

  class RenderingPass
  {
  public:
    MB_API
    virtual ~RenderingPass( ){}

    MB_API
    virtual void render( Renderer* renderer, BatchQueuePtr bq, Camera* c ) = 0;
    MB_API
    virtual void applyImageEffects( Renderer *renderer, Camera *camera );
    MB_API
    std::vector<ImageEffectPtr>& imageEffects( void )
    {
      return _imageEffects;
    }
    /*MyFBO* getSBuffer( Renderer* r );
    MyFBO* getDBuffer( Renderer* r );*/
  protected:
    std::vector< ImageEffectPtr > _imageEffects;

  private:
    void swapBuffers( Renderer* r );

    /*static const char* SRC_BUFFER_NAME;
    static const char* SRC_BUFFER_COLOR_TARGET_NAME;
    static const char* SRC_BUFFER_DEPTH_TARGET_NAME;

    static const char* DST_BUFFER_NAME;
    static const char* DST_BUFFER_COLOR_TARGET_NAME;
    static const char* DST_BUFFER_DEPTH_TARGET_NAME;

    // GBuffer
    static const char* GBUFFER_NAME;
    static const char* GBUFFER_POSITION_TARGET_NAME;
    static const char* GBUFFER_NORMAL_TARGET_NAME;
    static const char* GBUFFER_DIFFUSE_TARGET_NAME;
    static const char* GBUFFER_BUFFER_DEPTH_TARGET_NAME;*/
  };
}

#endif /* __MB_RENDERING_PASS__ */
