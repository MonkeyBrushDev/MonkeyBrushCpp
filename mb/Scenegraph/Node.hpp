#ifndef __MB_NODE__
#define __MB_NODE__

#include "../Components/Component.hpp"
#include <unordered_map>
#include <functional>
#include "../Visitors/Visitor.hpp"
#include "../Layer.hpp"

#include <mb/api.h>
#include <algorithm>
#include <string>

namespace mb
{
  class Quaternion;
  class EulerAngles
  {
  public:
    void setOnChangeCallback( const std::function<void( Quaternion )>& cb )
    {
      _cb = cb;
    }
    std::function<void( Quaternion )> _cb;
  };
  class Quaternion
  {
  public:
    void setOnChangeCallback( const std::function<void( EulerAngles )>& cb )
    {
      _cb = cb;
    }
    std::function<void( EulerAngles )> _cb;
  };
  class Transformation
  {
  public:
    void computeFrom( const Transformation&, const Transformation& )
    {
      std::cout << "Computing transform" << std::endl;
    }
    void translate( const float&, const float&, const float& )
    {
    }
  };

  class Node
  {
  public:
    MB_API
    Layer& layer( )
    {
      return _layer;
    }
  private:
    Layer _layer;

  public:
    MB_API
    Node( );
    MB_API
    Node( const std::string& name );
    MB_API
    virtual ~Node( void );
    MB_API
    std::string name( void ) const;
    MB_API
    void name( const std::string& name );
    std::string tag;
  protected:
    Node* _parent;
    std::string _name;

  public:
    MB_API
    void perform( Visitor &visitor );
    MB_API
    void perform( const Visitor &visitor );
    MB_API
    virtual void accept( Visitor &visitor );

  public:
    MB_API
    bool hasParent( void ) const;
    MB_API
    Node* parent( void );

    template<class NodeClass>
    NodeClass* parent( void );

    void parent( Node* p );

    MB_API
    void startComponents( void );
    MB_API
    void addComponent( Component* comp );
    MB_API
    void updateComponents( const float& dt );
    MB_API
    void detachAllComponents( void );
    MB_API
    void forEachComponent( std::function< void( Component * ) > callback );

    template <class T>
    bool hasComponent( void );
    template <class T>
    T* getComponent( void );
    template <class T>
    void removeComponent( void );
    template <class T>
    void removeComponents( void );
    template <class T>
    T* componentInParent( void );

    MB_API
    Component* getComponentByName( const std::string& name );
    MB_API
    std::vector<Component*> getComponentsByName( const std::string& name );

  protected:
    std::unordered_multimap<std::string, Component*> _components;

  public:
    void setLocal( const Transformation &t )
    {
      _local = t;
    }
    const Transformation &getLocal( void ) const
    {
      return _local;
    }
    Transformation &local( void )
    {
      return _local;
    }

    void setWorld( const Transformation &t )
    {
      _world = t;
    }
    const Transformation &getWorld( void ) const
    {
      return _world;
    }
    Transformation &world( void )
    {
      return _world;
    }
  protected:
    Transformation _local;
    Transformation _world;
  };

  #include "Node.inl"
}

#endif /* __MB_NODE__ */
