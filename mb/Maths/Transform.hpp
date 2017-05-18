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
      const Vector3& getPosition( void ) const
      {
        return _position;
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

    protected:
      // OPTIMIZATION: If identity, discard multiplication on global matrices generation!!
      bool _isIdentity;
    };
}

#endif /* __MB_TRANSFORM__ */
