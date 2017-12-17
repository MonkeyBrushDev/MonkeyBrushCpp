#ifndef __MB_RENDER_TARGET__
#define __MB_RENDER_TARGET__

#include <mb/api.h>
#include <memory>
#include <vector>
#include "../Rendering/Texture.hpp"

namespace mb
{
  namespace pp
  {
    MB_API
    class RenderTargetOutput
    {
    public:
      enum AttachmentsPoint: short
      {
        Color0,
        Color1,
        Color2,
        Color3,
        Color4,
        Color5,
        Color6,
        Color7,
        Color8,
        Color9,
        Color10,
        Color11,
        Color12,
        Color13,
        Color14,
        Color15,
        Depth,
        Stencil,
        DepthStencil
      };
      MB_API
      RenderTargetOutput( void );
      MB_API
      RenderTargetOutput( const AttachmentsPoint& ap, Texture* t );
      MB_API
      void setTexture( Texture* t );
      MB_API
      void setAttachmentPoint( const AttachmentsPoint& ap );
    protected:
      AttachmentsPoint _attPoint;
      Texture* _texture;
    };
    typedef std::shared_ptr<RenderTargetOutput> RenderTargetOutputRef;
    class RenderTarget
    {
    public:
      MB_API
      RenderTarget( void );
      MB_API
      virtual ~RenderTarget( void );
      MB_API
      void addOutput( const RenderTargetOutputRef rto );
      MB_API
      void removeOutput( const RenderTargetOutputRef rto );
      MB_API
      std::vector< RenderTargetOutputRef > outputs( void ) const;
    protected:
      std::vector< RenderTargetOutputRef > _outputs;
    };
  }
}

#endif /* __MB_RENDER_TARGET__ */
