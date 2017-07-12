#include "ComputeShader.hpp"
#include "../Includes.hpp"

#ifdef MB_COMPUTE_SHADERS
  namespace mb
  {
    namespace compute
    {
      const void* ComputeBuffer::getData( void )
      {
        return _data;
      }
      void ComputeBuffer::setData( void* data )
      {
        _data = data;
      }
      ComputeShader::ComputeShader( const std::string& shaderSrc )
      {
        _program = new mb::Program( );
        _program->loadComputeShaderFromText( shaderSrc );
        _program->compileAndLink( );
        _program->autocatching( );

        _program->unuse( );
      }
      ComputeShader::~ComputeShader( )
      {
        delete _program;
      }
      void ComputeShader::dispatch( unsigned int threadGroupsX,
        unsigned int threadGroupsY, unsigned int threadGroupsZ )
      {
        _program->use( );
        glDispatchCompute( threadGroupsX, threadGroupsY, threadGroupsZ );
        glMemoryBarrier( GL_SHADER_STORAGE_BARRIER_BIT );
        _program->unuse( );
      }
    }
  }
#endif
