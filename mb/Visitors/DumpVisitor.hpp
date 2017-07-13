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

#ifndef __MB_DUMP_VISITOR__
#define __MB_DUMP_VISITOR__

#include "Visitor.hpp"
#include <string>

#include <mb/api.h>

namespace mb
{
  class DumpVisitor :
    public Visitor
  {
  public:
    MB_API
    virtual void traverse( Node *node ) override;
    MB_API
    virtual void visitNode( Node *node ) override;
    MB_API
    virtual void visitGroup( Group *group ) override;
    MB_API
    virtual void visitGeometry( Geometry *geometry ) override;
    MB_API
    virtual void visitCamera( Camera *camera ) override;
    MB_API
    virtual void visitLight( Light *light ) override;
  private:
    void _dumpNode( Node *node, const std::string& type );
    unsigned int _auxLevel = 0;
  };
}

#endif /* __NODESDUMP_VISITOR__ */
