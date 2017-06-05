#ifndef __MB_RENDER_BUFFER__
#define __MB_RENDER_BUFFER__

#include <mb/api.h>
#include "../Maths/Vector2.hpp"

namespace mb
{
  class RenderBuffer
  {
  public:
    MB_API
    virtual ~RenderBuffer( void );
    MB_API
    virtual void resize( const mb::Vector2& size ) = 0;
    MB_API
    void bind( void );
    MB_API
    void unbind( void );
  protected:
    RenderBuffer( const mb::Vector2& size, unsigned int format,
      unsigned int attachment, unsigned int samples = 4 );
    mb::Vector2 _size;
    unsigned int _format;
    unsigned int _attachment;
    unsigned int _samples;
    unsigned int _handler;
  };
  class RenderBufferTexture: public RenderBuffer
  {
  public:
    MB_API
    RenderBufferTexture( const mb::Vector2& size, unsigned int format,
      unsigned int attachment );
    MB_API
    virtual void resize( const mb::Vector2& size );
  };
  class RenderBufferMultisampleTexture: public RenderBuffer
  {
  public:
    MB_API
    RenderBufferMultisampleTexture(const mb::Vector2& size, unsigned int format,
      unsigned int attachment, unsigned int samples = 4);
    MB_API
    virtual void resize( const mb::Vector2& size );
  };
}

#endif /* __MB_RENDER_BUFFER__ */
