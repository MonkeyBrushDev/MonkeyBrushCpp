#ifndef __MB_TRANSFORM__
#define __MB_TRANSFORM__

#include "Vector3.hpp"

namespace mb
{
    class Transform
    {
    public:
      Vector3 _position;
      Vector3 _scale;
      Transform( void )
      {
        _position = Vector3( 0.0f );
        _scale = Vector3( 1.0f );
        _isIdentity = true;
      }
      bool isIdentity( void ) const { return _isIdentity; }
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
