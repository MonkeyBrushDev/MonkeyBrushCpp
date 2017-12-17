#include "RenderTarget.hpp"

namespace mb
{
  namespace pp
  {
    RenderTargetOutput::RenderTargetOutput( void )
    : _attPoint( AttachmentsPoint::Color0 )
    , _texture( nullptr )
    {
    }
    RenderTargetOutput::RenderTargetOutput( const AttachmentsPoint& ap, Texture* t )
    {
      setAttachmentPoint( ap );
      setTexture( t );
    }
    void RenderTargetOutput::setTexture( Texture* t )
    {
      _texture = t;
    }
    void RenderTargetOutput::setAttachmentPoint( const AttachmentsPoint& ap )
    {
      _attPoint = ap;
    }
    RenderTarget::RenderTarget( void )
    {
    }
    RenderTarget::~RenderTarget( void )
    {
    }
    void RenderTarget::addOutput( const RenderTargetOutputRef rto )
    {
      _outputs.push_back( rto );
    }
    void RenderTarget::removeOutput( const RenderTargetOutputRef rto )
    {
      auto it = std::find( _outputs.begin( ), _outputs.end( ), rto );
      if( it != _outputs.end( ) )
      {
        _outputs.erase( it );
      }
    }
    std::vector< RenderTargetOutputRef > RenderTarget::outputs( void ) const
    {
      return _outputs;
    }
  }
}
