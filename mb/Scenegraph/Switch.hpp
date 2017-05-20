#ifndef __MB_SWITCH__
#define __MB_SWITCH__

#include "Group.hpp"
#include <mb/api.h>

namespace mb
{
  class Switch :
    public Group
  {
  public:
    MB_API
    Switch( const std::string name );
    MB_API
    virtual ~Switch( );

    MB_API
    virtual void forEachNode( std::function<void( Node* )> cb );
    MB_API
    Node* currentNode( void );

    MB_API
    unsigned int getCurrentNodeIndex( void ) const;
    MB_API
    void setCurrentNodeIndex( unsigned int idx );

    MB_API
    void selectNextNode( void );
    MB_API
    void selectPreviousNode( void );

  private:
    unsigned int _currentIdx;
  };
}

#endif /* __MB_SWITCH__ */
