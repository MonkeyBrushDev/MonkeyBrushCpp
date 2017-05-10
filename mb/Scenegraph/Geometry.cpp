#include "Geometry.hpp"
#include <algorithm>

namespace mb
{
  void Geometry::accept( Visitor& v )
  {
    v.visitGeometry( this );
  }

  void Geometry::forEachPrimitive( std::function<void(Primitive*)> cb )
  {
    std::for_each( _primitives.begin( ), _primitives.end( ), cb );
  }
}
