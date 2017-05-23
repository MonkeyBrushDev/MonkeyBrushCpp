#ifndef __MB_RAY__
#define __MB_RAY__

#include <mb/api.h>

#include "../Boundings/BoundingVolume.hpp"

#include "Vector3.hpp"

namespace mb
{
  class Ray
  {
  public:
    Ray(const Vector3& origin = Vector3( 0.0f ),
      const Vector3& direction = Vector3( 0.0f ) );
    MB_API
    Vector3 origin( void ) const;
    MB_API
    Vector3 direction( void ) const;
    MB_API
    void origin( const Vector3& ori );
    MB_API
    void direction( const Vector3& dir );
    MB_API
    Vector3 getPoint( const float& t );

    Ray &operator=( const Ray& r )
    {
      _origin = r._origin;
      _direction = r._direction;
      return *this;
    }
    bool operator==( const Ray& r )
    {
      return ( _origin == r._origin && _direction == r._direction );
    }

    bool operator!=( const Ray& r )
    {
      return !( *this == r );
    }

    bool intersect( const BoundingVolume* )
    {
      // TODO
      return true;
    }
  protected:
    Vector3 _origin;
    Vector3 _direction;
  };
}

#endif /* __MB_RAY__ */
