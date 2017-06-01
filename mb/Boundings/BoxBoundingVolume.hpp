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

#ifndef __MB_BOX_BOUNDING_VOLUME__
#define __MB_BOX_BOUNDING_VOLUME__

#include <mb/api.h>

#include "../Maths/Vector3.hpp"
#include <vector>

#include "../Maths/Sphere.hpp"
#include "BoundingVolume.hpp"

namespace mb
{
  class BoxBoundingVolume : public BoundingVolume
  {
  public:
    MB_API
    BoxBoundingVolume( void );
    MB_API
    virtual BoundingVolume* clone( void );
    MB_API
    virtual const Vector3& getCenter( void ) const override;
    MB_API
    virtual float getRadius( void ) const override;
    MB_API
    virtual bool contains( const Vector3& point );
    MB_API
    virtual void computeFrom( const BoundingVolume *volume ) override;
    MB_API
    virtual void expand( const std::vector<Vector3>& points );
    MB_API
    virtual void expand( const Vector3& point );
    MB_API
    virtual void expand( const BoundingVolume *input );
    MB_API
    virtual int intersect( const Plane& plane ) const;
  protected:
    mb::Sphere _sphere;
  };
}

#endif /* __MB_BOX_BOUNDING_VOLUME__ */
