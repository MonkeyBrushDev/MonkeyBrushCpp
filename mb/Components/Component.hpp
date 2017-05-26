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
    // Invoked once when component is attached to a node
    virtual void onAttach( void );
    MB_API
    // Invoked once when component is detached from a node
    virtual void onDetach( void );
    MB_API
    bool isEnabled( void ) const;
    MB_API
    void enable( void );
    MB_API
    void disable( void );
    MB_API
    void setEnabled( const bool v );
    MB_API
    void toggle( void );
    MB_API
    virtual void onEnable( void ) { }
    MB_API
    virtual void onDisable( void ) { }
  private:
    void setNode( Node* n );
  protected:
    bool _enabled;
    MB_API
    Component( );
    Node* _node;
  };
}

#endif /* __MB_COMPONENT__ */
