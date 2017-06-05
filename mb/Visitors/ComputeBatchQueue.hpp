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

#ifndef __MB_FETCH_GEOMETRY__
#define __MB_FETCH_GEOMETRY__

#include "Visitor.hpp"
#include "../Rendering/BatchQueue.hpp"
#include <mb/api.h>

namespace mb
{
  class Group;
  class Geometry;
  class Light;

  class ComputeBatchQueue :
    public Visitor
  {
  public:
    MB_API
    ComputeBatchQueue( Camera* cam, BatchQueuePtr bq );
    MB_API
    virtual void traverse( Node* n ) override;
    MB_API
    virtual void visitGroup( Group* g ) override;
    MB_API
    virtual void visitGeometry( Geometry* n ) override;
    MB_API
    virtual void visitLight( Light* l ) override;
  protected:
    Camera* _camera;
    BatchQueuePtr _batch;
  };
}

#endif /* __MB_FETCH_GEOMETRY__ */
