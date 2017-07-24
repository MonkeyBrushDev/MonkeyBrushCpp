#include "ComputeShader.hpp"
#include "../Includes.hpp"

#ifdef MB_COMPUTE_SHADERS
  namespace mb
  {
    namespace compute
    {
      /*const void* ComputeBuffer::getData( void )
      {
        return _data;
      }
      void ComputeBuffer::setData( void* data )
      {
        _data = data;
      }*/
      ComputeShader::ComputeShader( const std::string& shaderSrc )
      {
        program = std::make_shared<mb::Program >( );
        program->loadComputeShaderFromText( shaderSrc );
        program->compileAndLink( );
        program->autocatching( );
      }
      ComputeShader::~ComputeShader( void )
      {
        _uniforms.clear( );
      }

      TUniforms& ComputeShader::uniforms( void )
      {
        return this->_uniforms;
      }
      UniformPtr& ComputeShader::uniform( const std::string& name )
      {
        return this->_uniforms[ name ];
      }
      void ComputeShader::addUniform( const std::string& name, UniformPtr u )
      {
        this->_uniforms[ name ] = u;
      }
      bool ComputeShader::hasUniform( const std::string& name )
      {
        return _uniforms.find( name ) != _uniforms.end( );
      }
      UniformPtr ComputeShader::operator[ ]( const std::string& name )
      {
        return uniform( name );
      }
      void ComputeShader::dispatch( unsigned int threadGroupsX,
        unsigned int threadGroupsY, unsigned int threadGroupsZ )
      {
        program->use( );
        glDispatchCompute( threadGroupsX, threadGroupsY, threadGroupsZ );
        //glMemoryBarrier( GL_SHADER_STORAGE_BARRIER_BIT );
        glMemoryBarrier( GL_SHADER_IMAGE_ACCESS_BARRIER_BIT );
        //program->unuse( );
        texId = 0;
        program->use( );
        for ( const auto& uniform : _uniforms )
        {
          auto type = uniform.second->type( );
          if ( type == UniformType::Float )
          {
            program->sendUniformf(
              uniform.first,
              uniform.second->value( ).cast< float >( )
              );
          }
          else if ( type == UniformType::Integer )
          {
            program->sendUniformi(
              uniform.first,
              uniform.second->value( ).cast< int >( )
              );
          }
          else if ( type == UniformType::Vector2 )
          {
            program->sendUniform2v(
              uniform.first,
              uniform.second->value( ).cast< mb::Vector2 >( ).data( )
              );
          }
          else if ( type == UniformType::Vector3 )
          {
            program->sendUniform3v(
              uniform.first,
              uniform.second->value( ).cast< mb::Vector3 >( ).data( )//.data( )
              );
          }
          else if ( type == UniformType::Vector4 )
          {
            //mb::Vector4 cc = uniform.second->value( ).cast< mb::Vector4 >( );
            program->sendUniform4v(
              uniform.first,
              uniform.second->value( ).cast< mb::Vector4 >( ).data( )
              );
          }
          else if ( type == UniformType::Matrix4 )
          {
            program->sendUniform4m(
              uniform.first,
              uniform.second->value( ).cast< mb::Matrix4 >( ).data( )
              );
          }
          else if ( type == UniformType::TextureSampler )
          {
            mb::Texture* tex = uniform.second->value( ).cast< mb::Texture* >( );
            if ( tex == nullptr ) continue;
            //tex->bind( texId );
            tex->bindToImageUnit( texId, GL_WRITE_ONLY/*, GL_RGBA16F*/ );
            //this->program->sendUniformi( uniform.first, texId );
            ++texId;
            // TODO: UNBIND TEXTURES IN UNUSE METHOD
          }
        }
        glDispatchCompute( threadGroupsX, threadGroupsY, threadGroupsZ );
        //glMemoryBarrier( GL_SHADER_STORAGE_BARRIER_BIT );
        glMemoryBarrier( GL_SHADER_IMAGE_ACCESS_BARRIER_BIT | GL_SHADER_STORAGE_BARRIER_BIT );
      }
    }
  }
#endif
