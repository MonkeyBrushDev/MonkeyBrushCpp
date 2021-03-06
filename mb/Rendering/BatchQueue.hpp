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

#ifndef __MB_BATCH_QUEUE__
#define __MB_BATCH_QUEUE__

#include <vector>
#include <map>

#include "../Scenegraph/Light.hpp"
#include "../Scenegraph/Geometry.hpp"
#include "../Scenegraph/Camera.hpp"

#include <mb/api.h>
#include <memory>

#include "../Maths/Matrix4.hpp"
#include "Material.hpp"

namespace mb
{
  struct Renderable
  {
    MaterialPtr material;
    Geometry* geometry;
    mb::Matrix4 modelTransform;
    float zDistance;
    Renderable( MaterialPtr m, Geometry* g,
      const mb::Matrix4& mt, float zDist )
    {
      this->material = m;
      this->geometry = g;
      this->modelTransform = mt;
      this->zDistance = zDist;
    }
  };

  class BatchQueue
  {
  public:
    enum class RenderableType
    {
      OPAQUE,
      TRANSPARENT,
      SHADOW
    };
    MB_API
    BatchQueue( void );
    MB_API
    virtual ~BatchQueue( void );
    MB_API
    std::vector<Renderable> renderables( RenderableType t );
    MB_API
    void pushGeometry( Geometry* g );
    MB_API
    void pushLight( Light * l );
    MB_API
    void reset( void );
    MB_API
    void setCamera( Camera* c );
    MB_API
    Camera* getCamera( void );
    MB_API
    const Matrix4 &getProjectionMatrix( void ) const { return _projectionMatrix; }
    MB_API
    const Matrix4 &getViewMatrix( void ) const { return _viewMatrix; }
  protected:
    Camera* _camera;
  public:
    std::vector< Light* > _lights;
  protected:
    Matrix4 _projectionMatrix;
    Matrix4 _viewMatrix;
    std::map< RenderableType, std::vector< Renderable >> _renderables;
  };
  typedef std::shared_ptr< BatchQueue > BatchQueuePtr;
}

#endif /* __MB_BATCH_QUEUE__ */
