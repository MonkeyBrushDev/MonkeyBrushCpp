#ifndef __MB_BUFFER_GEOMETRY__
#define __MB_BUFFER_GEOMETRY__

#include <map>
#include "BufferAttribute.hpp"

namespace mb
{
  class BufferGeometry
  {
  public:
  protected:
    std::map< std::string, IBufferAttribute* > _attributes;
    //IntBufferAttribute _index;
  };
}

#endif /* __MB_BUFFER_GEOMETRY__ */