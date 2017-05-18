#include "LOD.hpp"

namespace mb
{
  LOD::LOD( const std::string& name )
    : Group( name )
  {
  }
  void LOD::addChild( Node* node )
  {
    Group::addChild( node );
    unsigned int numChildren = this->numChildren( );
    if ( numChildren > _rangeList.size( ) )
    {
      float maxRange = !_rangeList.empty( ) ? _rangeList.back( ).second : 0.0f;
      _rangeList.resize( numChildren, MinMaxPair( maxRange, maxRange ) );
    }
  }
  void LOD::addChild( Node* node, const float& min, const float& max )
  {
    Group::addChild( node );
    unsigned int numChildren = this->numChildren( );
    if ( numChildren > _rangeList.size( ) )
    {
      _rangeList.resize( _children.size( ), MinMaxPair( min, min ) );
    }
    --numChildren;
    _rangeList[ numChildren ].first = min;
    _rangeList[ numChildren ].second = max;
  }

  void LOD::removeChild( Node* node )
  {
    unsigned int pos = std::find( _children.begin( ), _children.end( ), node ) 
      - _children.begin( );

    if ( pos < _rangeList.size() )
    {
      _rangeList.erase( _rangeList.begin( ) + pos );
    }
    Group::removeChild( node );
  }
  void LOD::removeChildren( void )
  {
    _rangeList.clear( );
    Group::removeChildren( );
  }
}