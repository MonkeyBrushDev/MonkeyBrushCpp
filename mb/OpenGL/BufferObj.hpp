#ifndef __MB_BUFFER_OBJ__
#define __MB_BUFFER_OBJ__

#include <mb/api.h>
#include "../Includes.hpp"

namespace mb
{
  class Buffer
  {
  public:
    MB_API
    Buffer( GLenum target );
    MB_API
    Buffer( GLenum target, unsigned int allocSize, const void* data, GLenum usage );
    MB_API
    virtual ~Buffer( void );

    MB_API
    void bind( void ) const;
    MB_API
    void bind( GLenum target ) const;
    MB_API
    void unbind( void ) const;

    MB_API
    void bufferData( unsigned int size, const GLvoid* data, GLenum usage );
    MB_API
    void bufferSubData( GLintptr offset, unsigned int size, const GLvoid* data );


    template<typename T>
    std::vector<T> extractData( unsigned int numElems ) const
    {
      std::vector< T > arrBuffer( numElems );
      glGetBufferSubData( _target, 0, sizeof( T ) * numElems, arrBuffer.data( ) );
      return arrBuffer;
    }

    MB_API
    inline unsigned int getHandler( void ) const { return _id; }
  protected:
    GLuint _id;
    unsigned int _size;
    GLenum _target;
    GLenum _usage;
  };

  class Vbo : public Buffer
  {
  public:
    MB_API
    Vbo( GLenum target );
    MB_API
    Vbo( GLenum target, unsigned int allocSize, const void* data, GLenum usage );
  };
  
  class Ubo : public Buffer
  {
  public:
    Ubo( void );
    Ubo( unsigned int allocSize, const void* data, GLenum usage );
    void bindBufferBase( GLuint index );
  };

  class Ssbo : public Buffer
  {
  public:
    MB_API
    Ssbo( unsigned int allocSize, const void* data = nullptr, 
      GLenum usage = GL_STATIC_DRAW );
    MB_API
    void bindBase( GLuint index );
    MB_API
    void unbindBase( void );
    MB_API
    void bufferStorage( unsigned int size, const void* data, 
      GLbitfield flags ) const;
  protected:
    unsigned int _base;
  };

  class Pbo : public Buffer
  {
  public:
    Pbo( GLenum target );
    Pbo( GLenum target, unsigned int allocSize, const void* data = nullptr,
      GLenum usage = GL_STATIC_DRAW );
  };
}

#endif /* __MB_BUFFER_OBJ__ */
