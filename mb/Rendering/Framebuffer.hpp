#ifndef __MB_FRAMEBUFFER__
#define __MB_FRAMEBUFFER__

#include <mb/api.h>
#include <vector>
#include <memory>

#include "../Maths/Color.hpp"
#include "../Rendering/Texture.hpp"

namespace mb
{
  class RenderTarget
  {
  public:
    enum class Type
    {
      COLOR_RGB,
      COLOR_RGBA,
      DEPTH
    };
    enum class Output
    {
      RENDER,
      TEXTURE
    };

  public:
    RenderTarget( Type t, Output o, uint32_t w, uint32_t h, bool floatTexture = false );
    //virtual ~RenderTarget( void );

    Type _type;
    Output _output;
    uint32_t _width;
    uint32_t _height;
    Texture* _texture;
    bool _floatTexture = false;
  protected:
    uint32_t _id;
  };

  class Framebuffer
  {
    public:
    Framebuffer( uint32_t w, uint32_t h );
    using RenderTargetPtr = std::shared_ptr< RenderTarget >;

    float getAspectRatio( void ) const
    { 
      return ( float ) _width / ( float ) _height;
    }
    void resize( uint32_t w, uint32_t h );
    uint32_t _width;
    uint32_t _height;
    mb::Color _clearColor;
    std::vector< RenderTargetPtr > _targets;
    uint32_t _fbo;

    void bind( void );
    void unbind( void );
  protected:
    void create( void );
  };

  class StandardFramebuffer: public Framebuffer
  {
  public:
    StandardFramebuffer( uint32_t w, uint32_t h );
    //virtual ~StandardFramebuffer( void );
  };
}

#endif /* __MB_FRAMEBUFFER__ */