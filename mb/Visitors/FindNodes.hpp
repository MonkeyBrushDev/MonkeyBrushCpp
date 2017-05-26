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
