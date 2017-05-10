#ifndef __MB_COMPONENT__
#define __MB_COMPONENT__

#include <iostream>
#include <mb/api.h>

namespace mb
{
  typedef std::string ComponentUID;
  #define IMPLEMENT_COMPONENT(__CLASS__) \
  public: \
    static mb::ComponentUID StaticGetUID( ) { \
    static std::string sUID = #__CLASS__; \
    return ( mb::ComponentUID ) sUID; /* This will be unique! */ \
    } \
    virtual mb::ComponentUID GetUID( ) const { return StaticGetUID( ); }

  class Node;

  MB_API
  class Component
  {
    friend class Node;
  public:
    MB_API
    virtual ComponentUID GetUID( ) const = 0;
    MB_API
    virtual ~Component( );
    MB_API
    Node* node( );
    MB_API
    virtual void update( const float &dt );
    MB_API
    virtual void start( void );
    MB_API
    virtual void onAttach( void );
    MB_API
    virtual void onDetach( void );
    bool activo = true;

  private:
    void setNode( Node* n );
  protected:
    MB_API
    Component( );
    Node* _node;
  };
}

#endif /* __MB_COMPONENT__ */
