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
    SphereBoundingVolume( void )
      : _sphere( Vector3( 0.0f, 0.0f, 0.0f ), 1.0f )
    {
    }
    MB_API
    explicit SphereBoundingVolume( const Vector3& center, float radius )
      : _sphere( center, radius )
    {
    }
    MB_API
    SphereBoundingVolume( const Sphere& sphere )
      : _sphere( sphere )
    {
    }
    MB_API
    virtual const Vector3& getCenter( void ) const override
    {
      return _sphere.getCenter( );
    }
    MB_API
    virtual float getRadius( void ) const override
    {
      return _sphere.getRadius( );
    }
    MB_API
    virtual bool contains( const Vector3& point )
    {
      float centerDiffSqr = ( _sphere.getCenter( ) - point ).getSquaredMagnitude( );
      float radiusSqr = _sphere.getRadius( ) * _sphere.getRadius( );
      return ( centerDiffSqr < radiusSqr );
    }
    MB_API
    virtual void expand( const std::vector<Vector3>& points )
    {
      if ( points.empty( ) )
      {
        _sphere.setCenter( Vector3::zero );
        _sphere.setRadius( 0.0f );
      }
      else
      {
        Vector3 max = points.front( );
        Vector3 min = points.front( );
        for ( const auto p : points )
        {
          if ( p[ 0 ] > max[ 0 ] ) max[ 0 ] = p[ 0 ];
          if ( p[ 1 ] > max[ 1 ] ) max[ 1 ] = p[ 1 ];
          if ( p[ 2 ] > max[ 2 ] ) max[ 2 ] = p[ 2 ];

          if ( p[ 0 ] < min[ 0 ] ) min[ 0 ] = p[ 0 ];
          if ( p[ 1 ] < min[ 1 ] ) min[ 1 ] = p[ 1 ];
          if ( p[ 2 ] < min[ 2 ] ) min[ 2 ] = p[ 2 ];
        }
        expand( min );
        expand( max );
      }
    }
    MB_API
    virtual void expand( const Vector3& point )
    {
      _sphere.expand( Sphere( point, 0.0f ) );
      setMin( -getRadius( ) * Vector3::one );
      setMax(  getRadius( ) * Vector3::one );
    }
  protected:
    Sphere _sphere;
  };
}

#endif /* __MB_SPHERE_BOUNDING_VOLUME__ */
