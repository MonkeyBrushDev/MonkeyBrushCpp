#ifndef __MB_PLANE__
#define __MB_PLANE__

#include "Vector3.hpp"
#include "Vector4.hpp"
#include "Ray.hpp"

namespace mb
{
  class Plane
  {
    Plane( const Vector3 &normal, float distance, bool forceNormalize = true )
    {
      setNormal( normal, forceNormalize );
      setDistance( distance );
    }
    Plane( const Vector4& v )
    {
      setNormal( Vector3( v.x( ), v.y( ), v.z( ) ) );
      setDistance( v.w( ) );
    }

    Plane( const Plane &plane )
      : _normal( plane._normal ),
      _distance( plane._distance )
    {
    }

    Plane& operator=( const Plane &plane )
    {
      _normal = plane._normal;
      _distance = plane._distance;
      return *this;
    }

    bool operator==( const Plane &plane )
    {
      return ( _normal == plane._normal && _distance == plane._distance );
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
    float getDistance( void ) const
    {
      return _distance;
    }
    void setDistance( float cte )
    {
      _distance = cte;
    }
    float getDistanceToPoint( const Vector3& inPt )
    {
      return Vector3::dot( this->_normal, inPt ) + this->_distance;
    }
    bool getSide( const Vector3& inPt )
    {
      return Vector3::dot( this->_normal, inPt ) + this->_distance > 0.0f;
    }
    bool sameSide( const Vector3& inPt0, const Vector3& inPt1)
    {
      float distanceToPoint = getDistanceToPoint( inPt0 );
      float distanceToPoint2 = getDistanceToPoint( inPt1 );
      return (distanceToPoint > 0.0f && distanceToPoint2 > 0.0f) ||
             (distanceToPoint <= 0.0f && distanceToPoint2 <= 0.0f);
    }
    bool raycast( const Ray& ray, float& enter )
    {
      float num = Vector3::dot( ray.direction( ), this->_normal );
      float num2 = -Vector3::dot( ray.origin( ), this->_normal ) - this->_distance;
      bool result;
      if ( Mathf::approximately( num, 0.0f ) )
      {
        enter = 0.0f;
        result = false;
      }
      else
      {
        enter = num2 / num;
        result = (enter > 0.0f);
      }
      return result;
    }
  protected:
    Vector3 _normal;
    float _distance;
  };
}

#endif /* __MB_PLANE__ */
