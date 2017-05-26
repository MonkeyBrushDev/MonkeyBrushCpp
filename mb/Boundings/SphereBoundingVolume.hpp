#ifndef __MB_SPHERE_BOUNDING_VOLUME__
#define __MB_SPHERE_BOUNDING_VOLUME__

#include <mb/api.h>

#include "../Maths/Vector3.hpp"
#include <vector>

#include "../Maths/Sphere.hpp"
#include "BoundingVolume.hpp"

namespace mb
{
  class SphereBoundingVolume : public BoundingVolume
  {
  public:
    MB_API
    SphereBoundingVolume( void );
    MB_API
    explicit SphereBoundingVolume( const Vector3& center, float radius );
    MB_API
    SphereBoundingVolume( const Sphere& sphere );
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
    Sphere _sphere;
  };
}

#endif /* __MB_SPHERE_BOUNDING_VOLUME__ */
