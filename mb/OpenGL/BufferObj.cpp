#include "BufferObj.hpp"

namespace mb
{
  Buffer::Buffer( GLenum target )
    : _id( 0 )
    , _size( 0 )
    , _target( target )
    , _usage( GL_DYNAMIC_DRAW )
  {
    glCreateBuffers( 1, &_id );
  }
  Buffer::Buffer( GLenum target, unsigned int allocSize,
    const void* data, GLenum usage )
    : _id( 0 )
    , _size( allocSize )
    , _target( target )
    , _usage( usage )
  {
    glCreateBuffers( 1, &_id );
    glBufferData( _target, _size, data, _usage );
  }
  Buffer::~Buffer( void )
  {
    glDeleteBuffers( 1, &_id );
  }
  void Buffer::bind( void ) const
  {
    glBindBuffer( _target, _id );
  }
  void Buffer::bind( GLenum target ) const
  {
    glBindBuffer( target, _id );
  }
  void Buffer::unbind( void ) const
  {
    glBindBuffer( _target, 0 );
  }
  void Buffer::bufferData( unsigned int size, const GLvoid* data,
    GLenum usage )
  {
    _size = size;
    _usage = usage;
    glBufferData( _target, _size, data, _usage );
  }
  void Buffer::bufferSubData( GLintptr offset, unsigned int size,
    const GLvoid *data )
  {
    glBufferSubData( _target, offset, size, data );
  }


  Vbo::Vbo( GLenum target )
    : Buffer( target )
  {
  }
  Vbo::Vbo( GLenum target, unsigned int allocSize, const void* data,
    GLenum usage )
    : Buffer( target, allocSize, data, usage )
  {
  }


  Ubo::Ubo( void )
    : Buffer( GL_UNIFORM_BUFFER )
  {
    _usage = GL_DYNAMIC_DRAW;
  }
  Ubo::Ubo( unsigned int allocSize, const void* data, GLenum usage )
    : Buffer( GL_UNIFORM_BUFFER )
  {
    bufferData( allocSize, data, usage );
  }
  void Ubo::bindBufferBase( GLuint index )
  {
    glBindBufferBase( _target, index, _id );
  }


  Ssbo::Ssbo( unsigned int allocSize, const void* data,
    GLenum usage )
    : Buffer( GL_SHADER_STORAGE_BUFFER, allocSize, data, usage )
    , _base( 0 )
  {
  }
  void Ssbo::bindBase( GLuint index )
  {
    glBindBufferBase( _target, _base, 0 );
    _base = index;
  }
  void Ssbo::unbindBase( void )
  {
    glBindBufferBase( _target, _base, 0 );
    _base = 0;
  }
  void Ssbo::bufferStorage( unsigned int size, const void* data,
      GLbitfield flags ) const
  {
    glBufferStorage( _target, size, data, flags );
  }


  Pbo::Pbo( GLenum target )
    : Buffer( target )
  {
    _usage = GL_STREAM_DRAW;
  }
  Pbo::Pbo( GLenum target, unsigned int allocSize, const void* data, GLenum usage )
    : Buffer( target, allocSize, data, usage )
  {
  }
}
