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

#ifndef __MB_GROUP__
#define __MB_GROUP__

#include "Node.hpp"
#include <mb/api.h>

namespace mb
{
  class Group;
  typedef std::shared_ptr< Group > GroupPtr;
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
    unsigned int getNumChildren( void ) const;

    MB_API
    virtual void addChild( Node* node );
    MB_API
    virtual void removeChild( Node* node );
    MB_API
    virtual void removeChildren( void );
    MB_API
    Node* nodeAt( unsigned int idx );

    template<typename T>
    T* nodeAt( unsigned int idx )
    {
      return static_cast< T* >( nodeAt( idx ) );
    }
    MB_API
    void insertChild( unsigned int idx, Node* node );
    MB_API
    void removeChild( unsigned int idx );
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
