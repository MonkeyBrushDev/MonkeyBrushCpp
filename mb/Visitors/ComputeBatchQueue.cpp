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

#include "ComputeBatchQueue.hpp"
#include "../Scenegraph/Camera.hpp"
#include "../Scenegraph/Group.hpp"
#include "../Scenegraph/Geometry.hpp"
#include "../Scenegraph/Light.hpp"

namespace mb
{
  ComputeBatchQueue::ComputeBatchQueue( Camera* c, BatchQueuePtr bq_ )
  : Visitor( )
  , _camera( c )
  , _batch( bq_ )
  {
  }

  void ComputeBatchQueue::visitGroup( Group *group )
  {
    // No ejecutamos culling de la cámara
    //  sobre los grupos porque los hijos pueden
    //  tener nodos útiles (?)
    Visitor::visitGroup( group );
  }

  void ComputeBatchQueue::traverse( Node* node )
  {
    _batch->reset( );
    _batch->setCamera( _camera );

    /*if ( _camera != nullpr )
    {
      _camera->computeCullingPlanes( );
    }*/

    Visitor::traverse( node );
  }

  void ComputeBatchQueue::visitGeometry( Geometry *geometry )
  {
    // TODO: Culled frustum culling

    if ( _camera != nullptr &&
      _camera->layer( ).check( geometry->layer( ) ) )
    {
      _batch->pushGeometry( geometry );
    }
  }

  void ComputeBatchQueue::visitLight( Light *light )
  {
    _batch->pushLight( light );
  }
}
