#ifndef __MB_LOD__
#define __MB_LOD__

#include "Group.hpp"

namespace mb
{
  class LOD : public Group
  {
  public:
    MB_API
    LOD( const std::string& name );
    MB_API
    virtual void addChild( Node* node );
    MB_API
    virtual void addChild( Node* node, const float& min, const float& max );
    MB_API
    virtual void removeChild( Node* node );
    MB_API
    virtual void removeChildren( void );

    typedef std::pair<float, float> MinMaxPair;
    typedef std::vector<MinMaxPair> RangeList;

  protected:
    RangeList _rangeList;
  };
}

#endif /* __MB_LOD__ */