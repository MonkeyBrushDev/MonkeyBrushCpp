#ifndef __MB_BOUNDING_VOLUME__
#define __MB_BOUNDING_VOLUME__

#include <mb/api.h>

#include "../Maths/Vector3.hpp"
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
    virtual bool contains( const Vector3& point ) = 0;
    virtual void expand( const Vector3& point ) = 0;
    // TODO: Use Vector3* points, unsigned int size ??
    virtual void expand( const std::vector<Vector3>& points ) = 0;
  private:
    Vector3 _min;
    Vector3 _max;
  };
}

#endif /* __MB_BOUNDING_VOLUME__ */
