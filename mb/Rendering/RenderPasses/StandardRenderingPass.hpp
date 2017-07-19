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

#ifndef __MB_STANDARD_RP__
#define __MB_STANDARD_RP__

#include "RenderingPass.hpp"

#include "../Renderer.hpp"
#include "../BatchQueue.hpp"

namespace mb
{
  class StandardRenderingPass: public RenderingPass
  {
  public:

    MB_API
    void beginRender( Renderer* renderer, BatchQueuePtr bq );
    MB_API
    void render( Renderer* renderer, BatchQueuePtr bq, Camera* c );

  protected:

    void beginRenderOpaqueObjects( Renderer* renderer, BatchQueuePtr bq );
    void beginRenderTransparentObjects( Renderer* renderer, BatchQueuePtr bq );
    void beginRenderStandard( Renderer* r, Renderable& renderable );

    void renderOpaqueObjects(Renderer* renderer, BatchQueuePtr bq, Camera* c );
    void renderTransparentObjects(Renderer* renderer, BatchQueuePtr bq, Camera* c );
    void renderStandardGeometry(Renderer*, Renderable&, MaterialPtr );
  };
}

#endif /* __MB_STANDARD_RP__ */
