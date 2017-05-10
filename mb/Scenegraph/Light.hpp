#ifndef __MB_LIGHT__
#define __MB_LIGHT__

#include "Node.hpp"
#include <mb/api.h>

namespace mb
{
  class Light :
    public Node
  {
  public:
    MB_API
      Light( void );
    MB_API
    ~Light( void );

  public:
    MB_API
    virtual void accept( Visitor& v ) override;
  };
}

#endif /* __MB_LIGHT__ */
