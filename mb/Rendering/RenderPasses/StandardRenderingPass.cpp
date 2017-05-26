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

#include "StandardRenderingPass.hpp"

namespace mb
{
  void StandardRenderingPass::render( Renderer* renderer, BatchQueuePtr bq, Camera* c )
  {
    // computeShadows( )
    renderOpaqueObjects( renderer, bq, c );
    renderTransparentObjects( renderer, bq, c );
  }

  void StandardRenderingPass::renderOpaqueObjects( Renderer* renderer, BatchQueuePtr bq, Camera* /*c*/ )
  {
    auto renderables = bq->renderables( BatchQueue::RenderableType::OPAQUE );
    if ( renderables.empty( ) )
    {
      return;
    }
    std::cout << "Render OpaqueObjects" << std::endl;
    /*rq->each( renderables, {
      auto mat = r->material;
      mat->set( "projection", ... );
      mat->set( "view", ... );
      // if (isShadowEnabled( )) { }
      // if (isLightEnabled( )) { bindEachLight( ); }

      renderStandardGeometry( renderer, renderable->geometry, material, renderable->modelTransform );

      // if (isLightEnabled( )) { unbindEachLight( ); }
      // if (isShadowEnabled( )) { }

    });*/
    for ( auto& renderable : renderables )
    {
      // TODO: set projection and view

      renderStandardGeometry( renderer, renderable );
    }
  }
  void StandardRenderingPass::renderTransparentObjects( Renderer* renderer,
                                                        BatchQueuePtr bq, Camera* /*c*/ )
  {
    auto renderables = bq->renderables( BatchQueue::RenderableType::TRANSPARENT );
    if ( renderables.empty( ) )
    {
      return;
    }
    std::cout << "Render TransparentObjects" << std::endl;
    for ( auto& renderable : renderables )
    {
      // TODO: set projection and view

      renderStandardGeometry( renderer, renderable );
    }
  }
  void StandardRenderingPass::renderStandardGeometry( Renderer* /*renderer*/, Renderable* renderable )
  {
    renderable->geom->forEachPrimitive( [] ( Primitive *pr )
    {
      //std::cout << "Draw primitive" << std::endl;
      pr->render( );
    } );
  }
}
