#ifndef __MB_TRANSFORM__
#define __MB_TRANSFORM__

#include "Vector3.hpp"

namespace mb
{
  enum RotationOrder
  {
    OrderXYZ,
    OrderXZY,
    OrderYZX,
    OrderYXZ,
    OrderZXY,
    OrderZYX
  };
  enum Space
  {
    World,
    Self
  };
  class Transform
  {
  public:
    RotationOrder rotationOrder = RotationOrder::OrderXYZ;
    Vector3 _eulerAngles;
    Vector3 _position;
    Vector3 _scale;

    Transform( void )
    {
      _position = Vector3( 0.0f );
      _scale = Vector3( 1.0f );
      _isIdentity = true;
    }

    /*Vector3 getRight( void )
    {
      return this->getRotation( ) * Vector3::right;
    }
    void setRight( const Vector3& v )
    {
      setRotation( Quaternion::fromRotation( Vector3::right, v ) );
    }

    Vector3 getUp( void )
    {
      return this->getRotation( ) * Vector3::up;
    }
    void setUp( const Vector3& v )
    {
      setRotation( Quaternion::fromRotation( Vector3::up, v ) );
    }

    Vector3 getForward( void )
    {
      return this->getRotation( ) * Vector3::forward;
    }
    void setForward( const Vector3& v )
    {
      setRotation( Quaternion::fromRotation( Vector3::forward, v ) );
    }

    Vector3 transformDirection( const Vector3& direction )
    {
      Vector3 result;
      return result;
    }
    void translate( const Vector3& translation, Space relativeTo = Space::Self )
    {
      if ( relativeTo == Space::World )
      {
        this->_position += translation;
      }
      else
      {
        this->_position += this->transformDirection( translation );
      }
    }
    void translate( float x, float y, float z, Space relativeTo = Space::Self )
    {
      this->translate( x, y, z, relativeTo );
    }
    void translate( const Vector3& translation, const Transform* relativeTo )
    {
      if ( relativeTo != nullptr )
      {
        this->_position += relativeTo->transformDirection( translation );
      }
      else
      {
        this->_position += translation;
      }
    }
    void translate( float x, float y, float z, const Transform* relativeTo )
    {
      this->translate( Vector3( x, y, z ), relativeTo );
    }
    void rotate( const Vector3& eulerAngles, Space relativeTo = Space::Self )
    {
      Quaternion rhs = Quaternion::fromEuler( 
        eulerAngles.x( ), eulerAngles.y( ), eulerAngles.z( ) );
      if ( relativeTo == Space::Self )
      {
        this->_localRotation *= rhs;
      }
      else
      {
        this->_rotation *= Quaternion::inverse( this->getRotation( ) ) * rhs * this->getRotation( );
      }
    }
    void rotate( float xAngle, float yAngle, float zAngle )
    {
      this->rotate( Vector3( xAngle, yAngle, zAngle ), Space::Self );
    }*/
    bool isIdentity( void ) const {
      return _isIdentity;
    }
    Transform& operator= ( const Transform& t2 )
    {
      _position = t2._position;
      _scale = t2._scale;
      // TODO: Complete others variables
      _isIdentity = t2._isIdentity;
      return *this;
    }
    void translate( float x, float y, float z )
    {
      translate( Vector3( x, y, z ) );
    }
    void translate( const Vector3& pos )
    {
      setPosition( getPosition( ) + pos );
    }
    const Vector3& getPosition( void ) const
    {
      return _position;
    }
    void setPosition( const Vector3& pos )
    {
      _position = pos;
      _isIdentity = false;
    }
    void setPosition( float x, float y, float z )
    {
      _position[ 0 ] = x;
      _position[ 1 ] = y;
      _position[ 2 ] = z;
      _isIdentity = false;
    }
    void scale( float x, float y, float z )
    {
      scale( Vector3( x, y, z ) );
    }
    void scale( const Vector3& sc )
    {
      setScale( getScale( ) + sc );
    }
    const Vector3& getScale( void ) const
    {
      return _scale;
    }
    void setScale( const Vector3& sc )
    {
      _scale = sc;
      _isIdentity = false;
    }
    void setScale( float x, float y, float z )
    {
      _scale[ 0 ] = x;
      _scale[ 1 ] = y;
      _scale[ 2 ] = z;
      _isIdentity = false;
    }
    void computeFrom( const Transform& t1, const Transform& t2 )
    {
      if ( t1.isIdentity( ) )
      {
        *this = t2;
      }
      else if ( t2.isIdentity( ) )
      {
        *this = t1;
      }
      else
      {
        // TODO: Complete others variables
        _scale = t1._scale * t2._scale;
        _isIdentity = false;
      }
    }
    void lookAt( const Vector3& target, const Vector3& up = Vector3( 0.0f, 1.0f, 0.0f ) )
    {
      Vector3 dir = target - getPosition( );
      dir.normalize( );
      // _rotate.lookAt( dir, up );
    }
  protected:
    // OPTIMIZATION: If identity, discard multiplication on global matrices generation!!
    bool _isIdentity;
  };
}

#endif /* __MB_TRANSFORM__ */
