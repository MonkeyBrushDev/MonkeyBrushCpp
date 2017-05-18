#include "Geometry.hpp"
#include <algorithm>

namespace mb
{
  Geometry::Geometry( const std::string& name )
    : Node( name )
  {
    addComponent( new MeshRenderer( 1 ) );
  }
  Geometry::~Geometry( void )
  {
    removeAllPrimitives( );
  }
  void Geometry::removeAllPrimitives( void )
  {
    _primitives.clear( );
  }
  bool Geometry::hasPrimitives( void ) const
  {
    return !_primitives.empty( );
  }
  void Geometry::addPrimitive( Primitive* p )
  {
    _primitives.push_back( p );
  }
  void Geometry::removePrimitive( Primitive *p )
  {
    _primitives.erase( std::find( _primitives.begin( ), _primitives.end( ), p ) );
  }
  void Geometry::accept( Visitor& v )
  {
    v.visitGeometry( this );
  }

  void Geometry::forEachPrimitive( std::function<void(Primitive*)> cb )
  {
    std::for_each( _primitives.begin( ), _primitives.end( ), cb );
  }
}
