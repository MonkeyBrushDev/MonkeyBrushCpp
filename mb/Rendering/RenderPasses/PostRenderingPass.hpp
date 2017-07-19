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

#ifndef __MB_MB_POST_RP__
#define __MB_MB_POST_RP__

#include "RenderingPass.hpp"

namespace mb
{
  struct Renderable;
  class Renderer;
  class BatchQueue;

  class PostRenderingPass: public RenderingPass
  {
  public:
    MB_API
    PostRenderingPass( RenderingPass* sceneRP );
    MB_API
    virtual void beginRender( Renderer* renderer, BatchQueuePtr bq );
    MB_API
    void render( Renderer* renderer, BatchQueuePtr bq, Camera* cam );

  protected:
    RenderingPass *_sceneRenderingPass;

    int _fbo;

    // HARDCODED
    static int FBOCOUNTER;
  };
}

#endif /* __MB_POST_RP__ */
