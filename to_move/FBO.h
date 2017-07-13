class IRenderTarget
{

}

struct FramebufferAttachment
{
  ITexture* texture;
  uint32_t mipmapIndex;
  uint32_t layerIndex;
  FramebufferAttachment( )
    : texture( nullptr )
    , mipmapIndex( 0 )
    , layerIndex( 0 )
  {
  }
  FramebufferAttachment( ITexture* t, uint32_t mipmapIndex_ = 0,
    uint32_t layerIndex_ = 0)
    : texture( t )
    , mipmapIndex( mipmapIndex_ )
    , layerIndex( layerIndex_ )
  {
  }
}
class IFramebuffer: public IRenderTarget, public NonCopyable
{
};

class Framebuffer: public Renderer:IFramebuffer
{
public:
    virtual ~Framebuffer( void )
    {
      glDeleteFramebuffers( 1, &_openGLFBO );

      if( !_colorTextures.empty( ) )
      {
        for( unsigned int i = 0, l = _colorTextures.size( ); i < l; ++i )
        {
          delete _colorTextures[ i ];
        }
      }
      _colorTextures.clear( );
      if ( !_depthStencilTexture )
      {
        delete _depthStencilTexture;
      }
    }
    uint32_t getOpenGLFramebuffer( const ) const
    {
      return _openGLFBO;
    }
    uint32_t getNumColorTextures( void ) const
    {
      return _colorTextures.size( );
    }
    bool generateMipMaps( void ) const
    {
      return _generateMipmaps;
    }

    virtual void getSize( uint32_t& w, uint32_t& h ) const override;

    Framebuffer( OpenGLRenderer& renderer, uint32_t numColorAttachments, ... )
    {
      if( numColorAttachments > 0 )
      {
        _colorTextures.reserve( numColorAttachments );

      }
    }

protected:
    uint32_t _openGLFBO;
    std::vector< Renderer::ITexture* > _colorTextures;
    Renderer::ITexture* _depthStencilTexture;
    uin32_t _width;
    uin32_t _height;
    bool _generateMipmaps;
    bool _multiSampleRT;
};
