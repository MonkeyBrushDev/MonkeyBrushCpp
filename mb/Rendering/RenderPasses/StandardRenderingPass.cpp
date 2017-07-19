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


  void StandardRenderingPass::beginRender( Renderer* renderer, BatchQueuePtr bq )
  {
    beginRenderOpaqueObjects( renderer, bq );
    beginRenderTransparentObjects( renderer, bq );
  }

  void StandardRenderingPass::beginRenderOpaqueObjects( Renderer* renderer,
                                                        BatchQueuePtr bq )
  {
    auto renderables = bq->renderables( mb::BatchQueue::RenderableType::OPAQUE );
    if ( renderables.empty( ) )
    {
      return;
    }

    for( Renderable& renderable: renderables )
    {
      beginRenderStandard( renderer, renderable );
    }

  }

  void StandardRenderingPass::beginRenderTransparentObjects( Renderer* renderer,
                                                             BatchQueuePtr bq )
  {
    auto renderables = bq->renderables( mb::BatchQueue::RenderableType::TRANSPARENT );
    if ( renderables.empty( ) )
    {
      return;
    }

    for( Renderable& renderable: renderables )
    {
      beginRenderStandard( renderer, renderable );
    }
  }

  void StandardRenderingPass::beginRenderStandard( Renderer* r,
                                                   Renderable& renderable )
  {
    renderable.geometry->forEachPrimitive( [&] ( Primitive *pr )
    {
      r->beginRenderToPrimitive( pr );
    });

  }

  void StandardRenderingPass::render( Renderer* renderer,
                                      BatchQueuePtr bq, Camera* c )
  {
    // computeShadows( )
    renderOpaqueObjects( renderer, bq, c );
    renderTransparentObjects( renderer, bq, c );
  }

  void StandardRenderingPass::renderOpaqueObjects( Renderer* renderer,
                                                   BatchQueuePtr bq, Camera* /*c*/ )
  {
    auto renderables = bq->renderables( mb::BatchQueue::RenderableType::OPAQUE );
    if ( renderables.empty( ) )
    {
      return;
    }
//    std::cout << "Render OpaqueObjects" << std::endl;
    mb::Matrix4 projection = bq->getProjectionMatrix( );
    mb::Matrix4 view = bq->getViewMatrix( );


    unsigned int numLights = bq->_lights.size( );

    for( Renderable& renderable: renderables )
    {
      auto material = renderable.material;
      if ( !material ) continue;
      material->uniform( MB_PROJ_MATRIX )->value( projection );
      material->uniform( MB_VIEW_MATRIX )->value( view );

      // BIND LIGHTS
      // TODO: NOT BEST OPTION
      if ( material->hasUniform( "mb_NumLights" ) )
      {
        material->uniform( "mb_NumLights" )->value( numLights );

        for ( unsigned int i = 0; i < numLights && i < 5; ++i )
        {
          std::string lightPosName = std::string( "mb_LightPosition[" ) +
            std::to_string( i ) + std::string( "]" );
          mb::Vector3 lightPos = bq->_lights[ i ]->getPosition( );
          mb::Vector4 lp = mb::Vector4( lightPos.x( ), lightPos.y( ), lightPos.z( ), 1.0 );
          material->uniform( lightPosName )->value( lp );

          std::string lightColorName = std::string( "mb_LightColor[" ) +
            std::to_string( i ) + std::string( "]" );
          mb::Color cc = bq->_lights[ i ]->getColor( );
          material->uniform( lightColorName )->value( mb::Vector3( cc.r( ), cc.g( ), cc.b( ) ) );
        }
      }

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
    //std::cout << "Render TransparentObjects" << std::endl;
    mb::Matrix4 projection = bq->getProjectionMatrix();
    mb::Matrix4 view = bq->getViewMatrix();
    for ( auto& renderable : renderables )
    {
      auto material = renderable.material;
      if ( !material ) continue;

      material->uniform( MB_PROJ_MATRIX )->value( projection );
      material->uniform( MB_VIEW_MATRIX )->value( view );

      renderStandardGeometry( renderer, renderable, material );
    }
  }
  void StandardRenderingPass::renderStandardGeometry( Renderer* r,
                                                      Renderable& renderable,
                                                      MaterialPtr m )
  {
    m->uniform( MB_MODEL_MATRIX )->value( renderable.modelTransform );
    // TODO: MOVE TO ANOTHER ZONE Material::use( Renderer* )

    auto state = m->getState( );
    r->setBlendingState( &state.getBlending( ) );
    r->setDepthState( &state.getDepth( ) );
    r->setCullState( &state.getCulling( ) );
    r->setStencilState( &state.getStencil( ) );
    r->setWireframeState( &state.getWireframe( ) );

    m->use( );
    renderable.geometry->forEachPrimitive( [&] ( Primitive *pr )
    {
      r->drawPrimitive( pr );
    } );

    //m->unuse( );
  }
}
