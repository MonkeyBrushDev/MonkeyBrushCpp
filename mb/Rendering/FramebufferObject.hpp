#ifndef __MB_FRAMEBUFFER_OBJECT__
#define __MB_FRAMEBUFFER_OBJECT__

#include <mb/api.h>
#include "../Maths/Color.hpp"
#include "RenderTarget.hpp"

#include <map>

namespace mb
{
  class FramebufferObject
  {
  public:
    MB_API
    FramebufferObject( unsigned int width, unsigned int height );
    MB_API
    virtual ~FramebufferObject( void ) { }

    MB_API
    unsigned int getWidth( void ) const { return _width; }
    MB_API
    unsigned int getHeight( void ) const { return _height; }

    MB_API
    void resize( unsigned int w, unsigned int h );

    MB_API
    const mb::Color& getClearColor( void ) const { return _clearColor; }
    MB_API
    void setClearColor( const mb::Color& color ) { _clearColor = color; }


    const std::map< std::string, RenderTarget >& getRenderTargets( void ) const
    {
      return _renderTargets;
    }

  protected:
    unsigned int _width;
    unsigned int _height;
    mb::Color _clearColor;
    std::map< std::string, RenderTarget > _renderTargets;
  };

  class StandardFramebuffer: public FramebufferObject
  {
  public:
    MB_API
    StandardFramebuffer( unsigned int w, unsigned int h );
    MB_API
    virtual ~StandardFramebuffer( void );
  };

  class GBuffer: public FramebufferObject
  {
  public:
    MB_API
    GBuffer( unsigned int w, unsigned int h );
    MB_API
    virtual ~GBuffer( void );
  };
}

#endif /* __MB_FRAMEBUFFER_OBJECT__ */
