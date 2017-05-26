/**
 * Copyright (c) 2017, Monkey Brush
 * All rights reserved.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

#ifndef __MB_NODE__
#define __MB_NODE__

#include "../Components/Component.hpp"
#include "../Boundings/BoundingVolume.hpp"
#include <unordered_map>
#include <functional>
#include "../Visitors/Visitor.hpp"
#include "../Layer.hpp"

#include "../Maths/Transform.hpp"

#include <mb/api.h>
#include <algorithm>
#include <string>
#include <memory>

namespace mb
{
  class Node;
  typedef std::shared_ptr< Node > NodePtr;
  class Node
  {
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
  protected:
    Node* _parent;
    std::string _name;

  public:
    std::string tag;
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

    template< class T, typename ... Args >
    T* addComponent( Args&& ... args );
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
    /** TODO: More functions!
      - GetComponentsInParent<T>(bool includeInactives)
      - GetComponentsInChildren<T>(bool includeInactives)
      - FindNodesWithTag(string tag) NOTE: Global? Local?
    */

    MB_API
    Component* getComponentByName( const std::string& name );
    MB_API
    std::vector<Component*> getComponentsByName( const std::string& name,
      bool includeInactive = false );

  protected:
    std::unordered_multimap<std::string, Component*> _components;

  public:
    void setLocal( const Transform &t )
    {
      _local = t;
    }
    const Transform &getLocal( void ) const
    {
      return _local;
    }
    Transform &local( void )
    {
      return _local;
    }

    void setWorld( const Transform &t )
    {
      _world = t;
    }
    const Transform& getWorld( void ) const
    {
      return _world;
    }
    Transform& world( void )
    {
      return _world;
    }
    BoundingVolume* localBound( void )
    {
      return _localBound;
    }
    const BoundingVolume* getLocalBound( void ) const
    {
      return _localBound;
    }
    void setLocalBound( BoundingVolume* bound )
    {
      _localBound = bound ;
    }
    BoundingVolume* worldBound( void )
    {
      return _worldBound;
    }
    const BoundingVolume* getWorldBound( void ) const
    {
      return _worldBound;
    }
    void setWorldBound( BoundingVolume* bound )
    {
      _worldBound = bound;
    }
  protected:
    Transform _local;
    Transform _world;
    BoundingVolume* _localBound;
    BoundingVolume* _worldBound;

  public:
    void setEnabled( bool enabled )
    {
      _enabled = enabled;
    }
    bool isEnabled( void )
    {
      return _enabled;
    }

  private:
    bool _enabled = true;
  public:
    MB_API
    Layer& layer( )
    {
      return _layer;
    }
  private:
    Layer _layer;
  };

  #include "Node.inl"
}

#endif /* __MB_NODE__ */
