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

#ifndef __MB_LOD_NODE__
#define __MB_LOD_NODE__

#include "Switch.hpp"
#include <vector>

namespace mb
{
  class Camera;
  class LodNode : public Switch
  {
  public:
    LodNode( unsigned int numLOD );
    virtual ~LodNode( void );

    inline Vector3& localCenter( void )
    {
      return _localLodCenter;
    }
    inline const Vector3& getLocalCenter( void ) const
    {
      return _localLodCenter;
    }
    inline const Vector3& getWorldCenter( void ) const
    {
      return _worldLodCenter;
    }
    inline int getNumLOD( void ) const
    {
      return _numLevelsOfDetail;
    }
    inline float GeLocalMinDistance( int i ) const
    {
      return _localMinDist.at( i );
    }
    inline float GetLocalMaxDistance( int i ) const
    {
      return _localMaxDist.at( i );
    }
    inline float GetWorldMinDistance( int i ) const
    {
      return _worldMinDist.at( i );
    }
    inline float GetWorldMaxDistance( int i ) const
    {
      return _worldMaxDist.at( i );
    }
    void setModelDistance( int, float, float )
    {
    }
  protected:
    void setLOD( const Camera* camera );
    Vector3 _localLodCenter;
    Vector3 _worldLodCenter;

    int _numLevelsOfDetail;  // same as number of children of node
    std::vector<float> _localMinDist;
    std::vector<float> _localMaxDist;
    std::vector<float> _worldMinDist;
    std::vector<float> _worldMaxDist;
  };
}

#endif /* __MB_LOD_NODE__ */
