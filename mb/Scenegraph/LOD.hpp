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

#ifndef __MB_LOD__
#define __MB_LOD__

#include "Group.hpp"

namespace mb
{
  class LOD : public Group
  {
  public:
    MB_API
    LOD( const std::string& name );
    MB_API
    virtual void addChild( Node* node );
    MB_API
    virtual void addChild( Node* node, const float& min, const float& max );
    MB_API
    virtual void removeChild( Node* node );
    MB_API
    virtual void removeChildren( void );

    typedef std::pair<float, float> MinMaxPair;
    typedef std::vector<MinMaxPair> RangeList;

  protected:
    RangeList _rangeList;
  };
}

#endif /* __MB_LOD__ */