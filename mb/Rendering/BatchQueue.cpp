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

#include "BatchQueue.hpp"
#include "../Components/MeshRenderer.hpp"
#include "../Components/MaterialComponent.hpp"

namespace mb
{
  BatchQueue::BatchQueue( )
  {
    _renderables[ RenderableType::OPAQUE ] = std::vector<Renderable>( );
    _renderables[ RenderableType::TRANSPARENT ] = std::vector<Renderable>( );
  }

  BatchQueue::~BatchQueue( )
  {
    reset( );
  }

  void BatchQueue::reset( )
  {
    setCamera( nullptr );
    _lights.clear( );
    for ( auto &it : _renderables )
    {
      it.second.clear( );
    }
    _renderables.clear( );
  }
  void BatchQueue::setCamera( Camera* c )
  {
    if ( c!= nullptr )
    {
      _camera = c;
      _projectionMatrix = _camera->getProjection( );
      _viewMatrix = _camera->getView( );
    }
    else
    {
      _camera = nullptr;
      _projectionMatrix.makeIdentity( );
      _viewMatrix.makeIdentity( );
    }
  }
  Camera* BatchQueue::getCamera( void )
  {
    return _camera;
  }
  std::vector<Renderable> BatchQueue::renderables( RenderableType t )
  {
    return _renderables[ t ];
  }
  void BatchQueue::pushGeometry( Geometry* geometry )
  {
    /*auto mr = geometry->getComponent< MeshRenderer >( );
    if ( mr == nullptr )
    {
      return;
    }*/

    mb::MaterialComponent* materials = geometry->getComponent< mb::MaterialComponent >( );
    if ( materials == nullptr )
    {
      return;
    }

    auto renderType = RenderableType::OPAQUE;

    mb::PipelineState& state = materials->first()->state();

    if( state.blending().isEnabled( ) )
    {
      renderType = RenderableType::TRANSPARENT;
    }

    Renderable renderable(
      materials->first( ),
      geometry,
      geometry->world( ).computeModel( ),
      (
        getCamera( )->world( ).getPosition( ) -
        geometry->world( ).getPosition( )
      ).getSquaredMagnitude( )
    );

    auto queue = &_renderables[ renderType ];

    if( renderType == RenderableType::TRANSPARENT )
    {
      // Order back to front
      auto it = queue->begin( );
      while( it != queue->end( ) && it->zDistance >= renderable.zDistance )
      {
        ++it;
      }
      queue->insert( it, renderable );
    }
    else
    {
      // Order by material
      auto it = queue->begin( );
      auto mat1 = materials->first();
      while( it != queue->end( ) )
      {
        auto mat2 = renderable.geometry->getComponent< mb::MaterialComponent >( )->first();
        if( mat1 != mat2 )
        {
          ++it;
        } else { break; }
      }
      queue->insert( it, renderable );
      // TODO: Required order?
      //queue->push_back( renderable );
    }

    if ( geometry->castShadows( ) )
    {
      _renderables[ RenderableType::SHADOW ].push_back( renderable );
    }
  }
  void BatchQueue::pushLight( Light * l )
  {
    _lights.push_back( l );
  }
}
