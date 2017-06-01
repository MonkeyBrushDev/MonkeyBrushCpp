#ifndef __MB_ORBIT_COMPONENT__
#define __MB_ORBIT_COMPONENT__

namespace mb
{
  // TODO: WIP
  class OrbitComponent: public Component
  {
    IMPLEMENT_COMPONENT( OrbitComponent )
  public:
    OrbitComponent( Node* target_, float distance_ = 10.0f,
      float speed_ = 1.0f, bool smooth_ = true )
      : target( target_ )
      , distance( distance_ )
      , speed( speed_ )
      , smooth( smooth_ )
    {
    }
    virtual void update( const mb::Clock& )
    {
      /*if ( target )
      {
        if (smooth)
        {
          // Look at and dampen the rotation
          var rotation = Quaternion.LookRotation(target.position - transform.position);
          transform.rotation = Quaternion.Slerp(transform.rotation, rotation, Time.deltaTime * damping);
        }
        else
        {
          // Just lookat
            transform.LookAt(target);
        }
      }*/

    }
  public:
    Node* target;
    float distance;
    float speed;
    bool smooth;
  };
}

#endif /* __MB_ORBIT_COMPONENT__ */
