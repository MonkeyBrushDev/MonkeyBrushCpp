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

#include "Switch.hpp"

namespace mb
{
  class LOD : public Switch
  {
  public:
    MB_API
    LOD( const std::string& name, unsigned int levelsOfDetail )
      : Switch( name )
    {
      _levelsOfDetail = levelsOfDetail;

      _localMinDist.reserve( _levelsOfDetail );
      _localMaxDist.reserve( _levelsOfDetail );
      _worldMinDist.reserve( _levelsOfDetail );
      _worldMaxDist.reserve( _levelsOfDetail );
    }
    virtual ~LOD( void )
    {
      _localMinDist.clear( );
      _localMaxDist.clear( );
      _worldMinDist.clear( );
      _worldMaxDist.clear( );
    }

    MB_API
    inline int getNumLevelsOfDetail( void ) const { return _levelsOfDetail; }
    inline float getLocalMinDistance( unsigned int idx ) const { return _localMinDist[ i ]; }
    inline float getLocalMaxDistance( unsigned int idx ) const { return _localMaxDist[ i ]; }
    inline float getWorldMinDistance( unsigned int idx ) const { return _worldMinDist[ i ]; }
    inline float getWorldMaxDistance( unsigned int idx ) const { return _worldMaxDist[ i ]; }
    void setLocalDistance( unsigned int idx, float minDist, float maxDist )
    {
      if ( i < _levelsOfDetail )
      {
        _localMinDist[ i ] = minDist;
        _localMaxDist[ i ] = maxDist;
        _worldMinDist[ i ] = minDist;
        _worldMaxDist[ i ] = maxDist;

        return;
      }
      throw;
    }
  protected:
    void selectLevelOfDetails( const Camera* camera )
    {
      _worldLodCenter = node( )->getWorld( ) * _localLodCenter( );

      /*for( unsigned int i = 0; i < _levelsOfDetail; ++i )
      {
        _worldMinDist[ i ] = node
        _worldMaxDist[ i ] = node
      }*/

      setActiveChild( INVALID_CHILD );
      Vector3 diff = _worldLodCenter - camera->world( )->getPosition( );
      float dist = diff.lenght( );
      for( unsigned int i = 0; i < _levelsOfDetail; ++i )
      {
        if ( _worldMinDist[ i ] <= dist && dist < _worldMaxDist[ i ] )
        {
          setActiveChild( i );
          break;
        }
      }
    }

    int _levelsOfDetail;


    MB_API
    virtual void addChild( Node* node );
    MB_API
    virtual void addChild( Node* node, const float& min, const float& max );
    MB_API
    virtual void removeChild( Node* node );
    MB_API
    virtual void removeChildren( void );
    /*//MB_API
    //virtual void forEachNode( std::function< void( Node * ) > callback );
    MB_API
    void getObjectForDistance( float distance )
    {
      MinMaxPair mmp;
      for ( unsigned int i = 0, l = _rangeList.size( ); i < l; ++i )
      {
        mmp = _rangeList[ i ];
        if ( mmp.first >= distance && distance <= mmp.second )
        {
          return nodeAt( i );
        }
      }
      return nodeAt( 0 );
    }*/

    typedef std::pair<float, float> MinMaxPair;
    typedef std::vector<MinMaxPair> RangeList;

  protected:
    RangeList _rangeList;
  };
}

#endif /* __MB_LOD__ */
