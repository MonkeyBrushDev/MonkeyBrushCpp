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
#ifndef __MB_BOUNDING_VOLUME__
#define __MB_BOUNDING_VOLUME__

#include <mb/api.h>

#include "../Maths/Vector3.hpp"
#include "../Maths/Plane.hpp"
#include <vector>

namespace mb
{
  class BoundingVolume
  {
  public:
    virtual ~BoundingVolume( void ) { }
    virtual const Vector3& getCenter( void ) const = 0;
    virtual float getRadius( void ) const = 0;
    MB_API
    const Vector3& getMin( void ) const { return _min; }
    MB_API
    const Vector3& getMax( void ) const { return _max; }
  protected:
    void setMin( const Vector3& min ) { _min = min; }
    void setMax( const Vector3& max ) { _max = max; }
  public:
    virtual void computeFrom( const BoundingVolume *volume ) = 0;
    virtual bool contains( const Vector3& point ) = 0;
    virtual void expand( const Vector3& point ) = 0;
    // TODO: Use Vector3* points, unsigned int size ??
    virtual void expand( const std::vector<Vector3>& points ) = 0;
    virtual void expand( const BoundingVolume *other ) = 0;

    virtual int intersectPlane( const Plane& plane ) const = 0;
  private:
    Vector3 _min;
    Vector3 _max;
  };
}

#endif /* __MB_BOUNDING_VOLUME__ */
