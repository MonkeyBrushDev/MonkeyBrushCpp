#ifndef __MB_FIND_MB__
#define __MB_FIND_MB__

#include "Visitor.hpp"
#include <functional>
#include <vector>

#include "../Scenegraph/Node.hpp"

#include <mb/api.h>

namespace mb
{
  class FindNodes: public Visitor
  {
  public:
    using NodeSelector = std::function< bool( Node* ) >;
  public:
    MB_API
    FindNodes( NodeSelector sel );

    MB_API
    virtual void eachMatchNodes( std::function<void(Node* )> cb );

    MB_API
    virtual void reset( void ) override;

    MB_API
    virtual void visitNode( Node* n ) override;
    MB_API
    virtual void visitGroup( Group* n ) override;

    MB_API
    std::vector< Node* > matches( ) const
    {
      return _matches;
    }
  protected:
    NodeSelector _selector;
    std::vector< Node * > _matches;
  };
}

#endif /* __MB_FIND_MB__ */
