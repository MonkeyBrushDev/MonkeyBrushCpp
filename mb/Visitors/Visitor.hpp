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
