#include "Switch.hpp"

namespace mb
{
  Switch::Switch( const std::string name )
  : Group( name )
  , _currentIdx( 0 )
  {
  }

  Switch::~Switch( )
  {
    std::cout << "Destroy switch" << std::endl;
  }

  void Switch::forEachNode( std::function<void( Node* )> cb )
  {
    if ( !hasNodes( ) )
    {
      return;
    }
    Node* current = nodeAt( _currentIdx );
    if ( current != nullptr )
    {
      cb( current );
    }
  }

  void Switch::selectNextNode( void )
  {
    if ( !hasNodes( ) )
    {
      return;
    }
    _currentIdx = ( _currentIdx + 1 ) % numChildren( );
  }

  void Switch::selectPreviousNode( void )
  {
    if ( !hasNodes( ) )
    {
      return;
    }
    unsigned int nChildren = numChildren( );
    _currentIdx = ( _currentIdx + nChildren - 1 ) % nChildren;
  }

  Node* Switch::currentNode( void )
  {
    return nodeAt( _currentIdx );
  }

  unsigned int Switch::getCurrentNodeIndex( void ) const
  {
    return _currentIdx;
  }

  void Switch::setCurrentNodeIndex( unsigned int idx )
  {
    _currentIdx = idx;
  }
}
