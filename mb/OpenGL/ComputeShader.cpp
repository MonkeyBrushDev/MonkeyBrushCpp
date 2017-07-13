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
        program = new mb::Program( );
        program->loadComputeShaderFromText( shaderSrc );
        program->compileAndLink( );
        program->autocatching( );
      }
      ComputeShader::~ComputeShader( )
      {
        delete program;
      }
      void ComputeShader::dispatch( unsigned int threadGroupsX,
        unsigned int threadGroupsY, unsigned int threadGroupsZ )
      {
        program->use( );
        glDispatchCompute( threadGroupsX, threadGroupsY, threadGroupsZ );
        //glMemoryBarrier( GL_SHADER_STORAGE_BARRIER_BIT );
        glMemoryBarrier( GL_SHADER_IMAGE_ACCESS_BARRIER_BIT );
        //program->unuse( );
      }
    }
  }
#endif
