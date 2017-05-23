#include "Ray.hpp"

namespace mb
{
  Ray::Ray( const Vector3& origin, const Vector3& direction )
    : _origin( origin )
    , _direction( direction )
  {
  }
  Vector3 Ray::origin( void ) const
  {
    return this->_origin;
  }
  Vector3 Ray::direction( void ) const
  {
    return this->_direction;
  }
  void Ray::origin( const Vector3& ori )
  {
    this->_origin = ori;
  }
  void Ray::direction( const Vector3& dir )
  {
    this->_direction = dir;
  }
  Vector3 Ray::getPoint( const float& t )
  {
    return Vector3(
      this->_origin.x( ) + t * this->_direction.x( ),
      this->_origin.y( ) + t * this->_direction.y( ),
      this->_origin.z( ) + t * this->_direction.z( )
    );
  }
}
