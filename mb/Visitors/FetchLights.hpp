#ifndef __MB_FETCH_LIGHTS__
#define __MB_FETCH_LIGHTS__

#include "Visitor.hpp"
#include <vector>
#include <functional>

#include <mb/api.h>

namespace mb
{
  class FetchLights :
    public Visitor
  {
  public:
    MB_API
    FetchLights( );
    MB_API
    virtual ~FetchLights( );
    MB_API
    virtual void reset( void ) override;
    MB_API
    virtual void visitLight( Light* c ) override;
    MB_API
    bool hasLights( void ) const
    {
      return !_lights.empty( );
    }
    MB_API
    std::vector<Light*> lights( ) const
    {
      return _lights;
    }
    MB_API
    void forEachLight( std::function<void( Light* )> cb );
  protected:
    std::vector<Light*> _lights;
  };
}

#endif /* __MB_FETCH_LIGHTS__ */
