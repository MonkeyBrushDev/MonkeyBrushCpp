#ifndef __MB_COMPUTE_SHADER__
#define __MB_COMPUTE_SHADER__

#include <mb/api.h>
#include "Program.hpp"

#ifdef MB_COMPUTE_SHADERS
  namespace mb
  {
    namespace compute
    {
      class ComputeBuffer
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
      };
      class ComputeShader
      {
      public:
        MB_API
        ComputeShader( const std::string& shaderSrc );
        MB_API
        virtual ~ComputeShader( void );
        void dispatch( unsigned int threadGroupsX, unsigned int threadGroupsY,
          unsigned int threadGroupsZ );
        //void dispatchIndirect( ??? );
      //protected:
        mb::Program* program;  // TODO: Move to std::shared_ptr
      };
    }
  }
#endif

#endif /* __MB_COMPUTE_SHADER__ */
