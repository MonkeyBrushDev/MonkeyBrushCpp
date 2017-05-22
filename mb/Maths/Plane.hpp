#ifndef __MB_PLANE__
#define __MB_PLANE__

#include "Vector3.hpp"

namespace mb
{
  class Plane
  {
    Plane( const Vector3 &normal, float constant, bool forceNormalize = true )
    {
      setNormal( normal, forceNormalize );
      setConstant( constant );
    }

    Plane( const Plane &plane )
      : _normal( plane._normal ),
      _constant( plane._constant )
    {
    }

    Plane& operator=( const Plane &plane )
    {
      _normal = plane._normal;
      _constant = plane._constant;
      return *this;
    }

    bool operator==( const Plane &plane )
    {
      return ( _normal == plane._normal && _constant == plane._constant );
    }

    bool operator!=( const Plane &plane )
    {
      return !( *this == plane );
    }

    const Vector3 &getNormal( void ) const
    {
      return _normal;
    }
    void setNormal( const Vector3 &normal, bool forceNormalize = true )
    {
      _normal = normal;
      if ( forceNormalize )
      {
        _normal.normalize( );
      }
    }
    float getConstant( void ) const
    {
      return _constant;
    }
    void setConstant( float cte )
    {
      _constant = cte;
    }

  protected:
    Vector3 _normal;
    float _constant;
  };
}

#endif /* __MB_PLANE__ */
