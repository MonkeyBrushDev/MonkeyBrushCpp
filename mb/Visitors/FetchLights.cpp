#include "FetchLights.hpp"

namespace mb
{
  FetchLights::FetchLights( )
  {
  }

  FetchLights::~FetchLights( )
  {
  }

  void FetchLights::reset( void )
  {
    _lights.clear( );
    Visitor::reset( );
  }

  void FetchLights::visitLight( Light *c )
  {
    _lights.push_back( c );
  }

  void FetchLights::forEachLight( std::function< void( Light * ) > cb )
  {
    for ( auto& light : _lights ) {
      cb( light );
    }
    _lights.clear( );
  }
}
