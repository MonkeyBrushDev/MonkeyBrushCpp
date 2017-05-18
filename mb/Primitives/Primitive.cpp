#include "Primitive.hpp"

namespace mb
{
  Primitive::Type Primitive::type( void ) const
  {
    return _type;
  }
  Primitive::Primitive( Primitive::Type type )
    : _type( type )
  {
  }
  void Primitive::render( void )
  {
    //std::cout << "\t-Primitive '" << name << "'" << std::endl;
  }
}
