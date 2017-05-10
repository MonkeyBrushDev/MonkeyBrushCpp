#ifndef __MB_FETCH_CAMERAS__
#define __MB_FETCH_CAMERAS__

#include "Visitor.hpp"
#include <vector>
#include <functional>

#include <mb/api.h>

namespace mb
{
  class FetchCameras :
    public Visitor
  {
  public:
    MB_API
    FetchCameras( );
    MB_API
    virtual ~FetchCameras( );
    MB_API
    virtual void reset( void ) override;
    MB_API
    virtual void visitCamera( Camera* c ) override;
    MB_API
    bool hasCameras( void ) const
    {
      return !_cameras.empty( );
    }
    MB_API
    void forEachCamera( std::function<void( Camera* )> cb );
  protected:
    std::vector<Camera*> _cameras;
  };
}

#endif /* __MB_FETCH_CAMERA__ */
