#include "Quaternion.hpp"

namespace mb
{
  Quaternion::Quaternion( float x, float y, float z, float w )
  {
    this->_values[0] = x;
    this->_values[1] = y;
    this->_values[2] = z;
    this->_values[3] = w;
  }

  Quaternion::Quaternion( const Quaternion& q )
  {
    this->_values[0] = q.x();
    this->_values[1] = q.y();
    this->_values[2] = q.z();
    this->_values[3] = q.w();
  }

  Quaternion& Quaternion::operator=( const Quaternion& q )
  {
    return copy(q);
  }
  Quaternion& Quaternion::copy( const Quaternion& q )
  {
    x(q.x());
    y(q.y());
    z(q.z());
    w(q.w());
    return *this;
  }
}