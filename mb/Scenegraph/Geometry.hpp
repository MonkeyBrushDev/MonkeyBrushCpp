#ifndef __MB_GEOMETRY__
#define __MB_GEOMETRY__

#include "Node.hpp"
#include "../Components/MeshRenderer.hpp"
#include "../Primitives/Primitive.hpp"

#include <iostream>
#include <string>

namespace mb
{
  // TODO: Use shared_ptr instead raw pointers
  class Geometry: public Node
  {
  public:
    MB_API
      Geometry( const std::string& name = "Geometry" );
    MB_API
    virtual ~Geometry( void );
    MB_API
    void removeAllPrimitives( void );
    MB_API
    bool hasPrimitives( void ) const;
    MB_API
    void addPrimitive( Primitive* p );
    MB_API
    void removePrimitive( Primitive *p );
    MB_API
    void forEachPrimitive( std::function< void(Primitive* )> cb );
  protected:
    std::vector< Primitive* > _primitives;

  public:
    virtual void accept( Visitor& v ) override;
  };
}

#endif /* __MB_GEOMETRY__ */
