#ifndef __MB_GROUP__
#define __MB_GROUP__

#include "Node.hpp"
#include <mb/api.h>

namespace mb
{
  class Group :
    public Node
  {
  public:
    MB_API
    Group( const std::string name );
    MB_API
    virtual ~Group( );

    MB_API
    bool hasNodes( void ) const;
    MB_API
    unsigned int numChildren( void ) const;

    MB_API
    void addChild( Node* node );
    MB_API
    void removeChild( Node* node );
    MB_API
    void removeChildren( void );
    MB_API
    Node* nodeAt( unsigned int idx );

    template<typename T>
    T* nodeAt( unsigned int idx )
    {
      return static_cast< T* >( nodeAt( idx ) );
    }
    MB_API
    void insertChild( unsigned int idx, Node* node )
    {
      // TODO Insert at position (WARNING: CHECK position)
    }
    MB_API
    void removeChild( unsigned int idx )
    {
      // TODO: Same as insertChild warnings
    }

    // TODO: getNode (string)
    // TODO: T* getNode<T>(string)
    MB_API
    virtual void forEachNode( std::function< void( Node * ) > callback );
  protected:
    std::vector<Node*> _children;

  public:
    MB_API
    virtual void accept( Visitor& v );
  };
}

#endif /* __MB_GROUP__ */
