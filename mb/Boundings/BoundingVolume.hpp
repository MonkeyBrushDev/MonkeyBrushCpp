#ifndef __MB_BOUNDING_VOLUME__
#define __MB_BOUNDING_VOLUME__

namespace mb
{
  struct vec3
  {
    float x;
    float y;
    float z;
  };
  class BoundingVolume
  {
  public:
    virtual ~BoundingVolume( void ) { }
    virtual const vec3 center( void ) const = 0;
    virtual float radius( void ) const = 0;
    virtual BoundingVolume* clone( void ) const { return nullptr; }
    const vec3& min( void ) const { return _min; }
    const vec3& max( void ) const { return _max; }
  protected:
    void min( const vec3& min ) { _min = min; }
    void min( const vec3& max ) { _max = max; }
    BoundingVolume( void ) { }
  private:
    vec3 _min;
    vec3 _max;
  public:
    virtual void computeFrom( const BoundingVolume* v ) = 0;
    virtual void computeFrom( const BoundingVolume* v, const Transform& tf ) = 0;
    virtual void computeFrom( const vec3& min, const vec3& max ) = 0;

    virtual bool contains( const vec3& point ) const = 0;

    virtual bool testIntersection( const BoundingVolume* o ) const = 0;
    virtual bool testIntersection( const Sphere& o ) const = 0;
    virtual bool testIntersection( const Plane& o ) const = 0;
  };

  class SphereBoundingVolume: public BoundingVolume
  {
  public:
    SphereBoundingVolume( void )
      : _sphere( vec3( 0.0f, 0.0f, 0.0f ), 1.0f )
    {
    }
    SphereBoundingVolume( const vec3& center, const float& radius )
      : _sphere ( center, radius )
    {
    }
    explicit SphereBoundingVolume( const Sphere& sphere )
      : _sphere ( sphere )
    {
    }
    virtual ~SphereBoundingVolume( void )
    {
    }
    virtual const vec3& center( void ) const override
    {
      return _sphere.center( );
    }
    virtual float radius( void ) const override
    {
      return _sphere.radius( );
    }
  private:
    Sphere _sphere;
  public:
    virtual void computeFrom( const BoundingVolume* v ) override
    {
      computeFrom( v->center( ) + v->min( ), v->center( ) + v->max( ) );
    }
    virtual void computeFrom( const BoundingVolume* v, const Transform& tf )
    {
      vec3 newCenter;
      tf.applyToPoint( v->center(), newCenter );
      _sphere.center( newCenter );
      _sphere.radius( v->radius() * tf.scale() );

      setMin( -radius() * vec3( 1.0f, 1.0f, 1.0f ) );
      setMax( +radius() * vec3( 1.0f, 1.0f, 1.0f ) );
    }
    virtual void computeFrom( const vec3&, const vec3& )
    {

    }
    virtual bool contains( const vec3& point ) const
    {

    }

    virtual bool testIntersection( const BoundingVolume* o ) const
    {
      return o->testIntersection( _plane );
    }
    virtual bool testIntersection( const Sphere& o ) const
    {
      return Instersection::test( _sphere, o );
    }
    virtual bool testIntersection( const Plane& o ) const
    {
      return 0;
    }
  };

  class PlaneBoundingVolume: public BoundingVolume
  {
  public:
    PlaneBoundingVolume( void )
      : _center( 0.0f, 0.0f, 0.0f )
      , _plane( Plane( 0.0f, 1.0f, 0.0f, 0.0f ))
    {
    }
    explicit PlaneBoundingVolume( const Plane& p )
      : _center( 0.0f, 0.0f, 0.0f )
      , _plane( p )
    {
    }
    virtual ~PlaneBoundingVolume( void )
    {
    }
    virtual const vec3& center( void ) const override
    {
      return _center;
    }
    virtual float radius( void ) const override
    {
      return 0.0f;
    }
  private:
    vec3 _center;
    Plane _plane;
  public:
    virtual void computeFrom( const BoundingVolume* ) override
    {

    }
    virtual void computeFrom( const BoundingVolume*, const Transform& )
    {

    }
    virtual void computeFrom( const vec3&, const vec3& )
    {

    }
    virtual bool contains( const vec3& ) const
    {
      return false;
    }

    virtual bool testIntersection( const BoundingVolume* o ) const
    {
      return o->testIntersection( _plane );
    }
    virtual bool testIntersection( const Sphere& o ) const
    {

    }
    virtual bool testIntersection( const Plane& o ) const
    {
      return 0;
    }
  };
}

#endif /* __MB_BOUNDING_VOLUME__ */
