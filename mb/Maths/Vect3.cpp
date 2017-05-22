#include "Vect3.hpp"


namespace mb
{
    Vect3 Vect3::xAxis(1.0f, 0.0f, 0.0f);
    Vect3 Vect3::yAxis(0.0f, 1.0f, 0.0f);
    Vect3 Vect3::zAxis(0.0f, 0.0f, 1.0f);
    Vect3 Vect3::up(0.0f, 1.0f, 1.0f);

    Vect3::Vect3( float x, float y, float z )
    {
      this->_values.resize(3);
      this->_values[0] = x;
      this->_values[1] = y;
      this->_values[2] = z;
    }

    float Vect3::x( void ) const
    {
      return this->_values[0];
    }

    void Vect3::x( const float& v )
    {
      this->_values[0] = v;
    }

    float Vect3::y( void ) const
    {
      return this->_values[1];
    }

    void Vect3::y( const float& v )
    {
      this->_values[1] = v;
    }
    float Vect3::z( void ) const
    {
      return this->_values[2];
    }

    void Vect3::z( const float& v )
    {
      this->_values[2] = v;
    }

}//NS

