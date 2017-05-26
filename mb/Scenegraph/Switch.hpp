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
