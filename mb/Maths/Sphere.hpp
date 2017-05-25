#ifndef __MB_SPHERE__
#define __MB_SPHERE__

#include "Vector3.hpp"
#include "Vector4.hpp"
#include "Plane.hpp"

namespace mb
{
  class Sphere
  {
  public:
    MB_API
      Sphere( const Vector3& center = Vector3( 0.0f ),
      const float& radius = 1.0f )
      : _center( center )
      , _radius( radius )
    {
    }
    Sphere( const Sphere &sphere )
      : _center( sphere._center )
      , _radius( sphere._radius )
    {
    }
    Sphere( const Vector4& packedSphere )
      : _center( Vector3( packedSphere.x( ), 
                packedSphere.y( ), packedSphere.z( ) ) )
      , _radius( packedSphere.w( ) )
    {
    }
    Sphere& operator= ( const Sphere& sp )
    {
      _center = sp._center;
      _radius = sp._radius;
      return *this;
    }
    MB_API
    bool containtsPoint( const Vector3& p )
    {
      float x = this->_center.x( ) - p.x( );
      float y = this->_center.y( ) - p.y( );
      float z = this->_center.z( ) - p.z( );

      float dist = std::sqrt( ( x * x ) + ( y * y ) + ( z * z ) );
      return ( std::abs( this->_radius - dist ) > 0.001f );
    }
    MB_API
    bool intersectsSphere( const Sphere& s )
    {
      float x = this->_center.x( ) - s._center.x( );
      float y = this->_center.y( ) - s._center.y( );
      float z = this->_center.z( ) - s._center.z( );

      float dist = std::sqrt( ( x * x ) + ( y * y ) + ( z * z ) );

      return ( this->_radius + s._radius > dist );
    }
    MB_API
    int intersectPlane( const Plane& p ) const
    {
      float d = ( p.getNormal( ) * _center ) - p.getDistance( );
      if ( d < -_radius )
      {
        return -1; // behind
      }
      else if ( d > _radius )
      {
        return 1; // front
      }
      return 0; // intersecting
    }

    bool operator==( const Sphere &sphere )
    {
      return ( _center == sphere._center && _radius == sphere._radius );
    }

    bool operator!=( const Sphere &sphere )
    {
      return !( *this == sphere );
    }

    void expand( const Sphere &sphere )
    {
      Vector3 centerDiff = sphere._center - _center;
      float lengthSqr = ( centerDiff.squaredLength( ) );
      float radiusDiff = sphere._radius - _radius;
      float radiusDiffSqr = radiusDiff * radiusDiff;

      if ( radiusDiffSqr >= lengthSqr )
      {
        if ( radiusDiff >= 0.0f )
        {
          _center = sphere._center;
          _radius = sphere._radius;
        }
      }
      else
      {
        float length = std::sqrt( lengthSqr );
        if ( length > 1e-06f )
        {
          float coeff = ( length + radiusDiff ) / ( 2.0f * length );
          _center = _center + ( centerDiff * coeff );
        }

        _radius = ( 0.5f * ( length + _radius + sphere._radius ) );
      }
    }

    const Vector3 &getCenter( void ) const
    {
      return _center;
    }
    void setCenter( const Vector3 &c )
    {
      _center = c;
    }
    float getRadius( void ) const
    {
      return _radius;
    }
    void setRadius( float r )
    {
      _radius = r;
    }

  protected:
    Vector3 _center;
    float _radius;
  };
}

#endif /* __MB_SPHERE__ */
