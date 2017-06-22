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
    auto renderables = bq->renderables( mb::BatchQueue::RenderableType::OPAQUE );
    if ( renderables.empty( ) )
    {
      return;
    }
    std::cout << "Render OpaqueObjects" << std::endl;
    mb::Matrix4 projection = bq->getProjectionMatrix();
    mb::Matrix4 view = bq->getViewMatrix();
    for( Renderable& renderable: renderables  )
    {
      // TODO: BIND LIGHTS
      auto material = renderable.material;
      material->uniform("projection")->value(projection);
      material->uniform("view")->value(view);

      renderStandardGeometry(renderer, renderable, material);
      // TODO: UNBIND LIGHTS
    }
  }
  void StandardRenderingPass::renderTransparentObjects( Renderer* renderer,
                                                        BatchQueuePtr bq, Camera* /*c*/ )
  {
    auto renderables = bq->renderables( mb::BatchQueue::RenderableType::TRANSPARENT );
    if ( renderables.empty( ) )
    {
      return;
    }
    std::cout << "Render TransparentObjects" << std::endl;
    mb::Matrix4 projection = bq->getProjectionMatrix();
    mb::Matrix4 view = bq->getViewMatrix();
    for ( auto& renderable : renderables )
    {
      auto material = renderable.material;

      material->uniform("projection")->value(projection);
      material->uniform("view")->value(view);

      renderStandardGeometry( renderer, renderable, material );
    }
  }
  void StandardRenderingPass::renderStandardGeometry( Renderer*, Renderable& renderable, MaterialPtr m )
  {
    renderable.geometry->forEachPrimitive( [m] ( Primitive *pr )
    {
      m->use( );
      pr->render( );
      m->unuse( );
    } );
  }
}
