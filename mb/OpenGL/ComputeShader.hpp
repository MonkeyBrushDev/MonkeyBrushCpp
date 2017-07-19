#ifndef __MB_COMPUTE_SHADER__
#define __MB_COMPUTE_SHADER__

#include <mb/api.h>
#include "Program.hpp"
#include "../Rendering/Material.hpp"

#include "BufferObj.hpp"
#include <map>

#ifdef MB_COMPUTE_SHADERS
  namespace mb
  {
    namespace compute
    {
      /*class ComputeBuffer
      {
      public:
        // count: num elements
        // stride: size of one element in buffer
        MB_API
        ComputeBuffer( unsigned int count, unsigned int stride );
        MB_API
        const void* getData( void );
        MB_API
        void setData( void* data );
      protected:
        unsigned int _count;
        unsigned int _stride;
        void* _data;
      };*/
      class ComputeShader
      {
      public:
        MB_API
        ComputeShader( const ComputeShader& cs )
          : program(cs.program )
        {
          for ( auto& kv : cs._uniforms )
          {
            this->addUniform( kv.first, UniformPtr( kv.second->clone( ) ) );
          }

          program = cs.program;
        }
        MB_API
        ComputeShader( const std::string& shaderSrc );
        MB_API
        virtual ~ComputeShader( void );
        MB_API
        void dispatch( unsigned int threadGroupsX, unsigned int threadGroupsY,
          unsigned int threadGroupsZ );
        MB_API
        TUniforms& uniforms( void );
        MB_API
        UniformPtr& uniform( const std::string& name );
        MB_API
        void addUniform( const std::string& name, UniformPtr u );
        MB_API
        bool hasUniform( const std::string& name );
        MB_API
        UniformPtr operator[ ]( const std::string& name );
        MB_API
        virtual ComputeShader* clone( void ) const
        {
          return new ComputeShader( *this );
        }
        //void dispatchIndirect( ??? );
      //protected:
        std::shared_ptr< mb::Program > program;
        unsigned int texId;
        TUniforms _uniforms;

        std::map<unsigned int, mb::Ssbo*> buffers;
      };
    }
  }
#endif

#endif /* __MB_COMPUTE_SHADER__ */
