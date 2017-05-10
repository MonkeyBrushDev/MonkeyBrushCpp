#ifndef __MB_GEOMETRY__
#define __MB_GEOMETRY__

#include "Node.hpp"
#include "../components/MeshRenderer.hpp"
#include "../Primitives/Primitive.hpp"

#include <iostream>
#include <string>

namespace mb
{
  class Geometry: public Node
  {
  public:
    MB_API
    Geometry( const std::string& name = "" )
      : Node( name )
    {
      addComponent( new MeshRenderer( 1 ) );
    }

    virtual ~Geometry( )
    {
      removeAllPrimitives( );
    }
    void removeAllPrimitives( void )
    {
      _primitives.clear( );
    }

    bool hasPrimitives( void ) const
    {
      return !_primitives.empty( );
    }

    void addPrimitive( Primitive* p )
    {
      _primitives.push_back( p );
    }
    void removePrimitive( Primitive *p )
    {
      // TODO: Worst code in the world xD
      _primitives.erase( std::find( _primitives.begin( ), _primitives.end( ), p ) );
    }
    void forEachPrimitive( std::function< void(Primitive* )> cb );

  protected:
    std::vector< Primitive* > _primitives;

  public:
    virtual void accept( Visitor& v ) override;
  };
}

#endif /* __MB_GEOMETRY__ */
