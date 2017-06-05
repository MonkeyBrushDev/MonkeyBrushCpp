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

#ifndef __MB_LAMBDA_VISITOR__
#define __MB_LAMBDA_VISITOR__

#include <functional>
#include "Visitor.hpp"
#include <mb/api.h>

namespace mb
{
  class LambdaVisitor :
    public Visitor
  {
  private:
    typedef std::function<void( Node* )> CallbackType;
  public:
    MB_API
    LambdaVisitor( CallbackType cb );
    MB_API
    virtual void visitNode( Node* n ) override;
    MB_API
    virtual void visitGroup( Group* g ) override;
  private:
    CallbackType _callback;
  };
}

#endif /* __MB_LAMBDA_VISITOR__ */
