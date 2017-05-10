#ifndef __MB_VISITOR__
#define __MB_VISITOR__

#include <mb/api.h>

namespace mb
{
  class Node;
  class Geometry;
  class Group;
  class Camera;
  class Light;

  class Visitor
  {
  protected:
    Visitor( ) {}
  public:
    MB_API
    virtual ~Visitor( );
    MB_API
    virtual void reset( void );
    MB_API
    virtual void traverse( Node* node );
    MB_API
    virtual void visitNode( Node *node );
    MB_API
    virtual void visitGroup( Group *group );
    MB_API
    virtual void visitCamera( Camera *camera );
    MB_API
    virtual void visitLight( Light* light );
    MB_API
    virtual void visitGeometry( Geometry *geometry );
  private:
    Visitor( const Visitor& );
    Visitor &operator= ( const Visitor& );
  };
}

#endif /* __MB_VISITOR__ */
