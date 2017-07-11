#ifndef __MB_OPENGLMAPPING__
#define __MB_OPENGLMAPPING__

namespace mb
{
  namespace gl
  {
    extern unsigned int glOGLSrcBlend[ 11 ];
    extern unsigned int glOGLDstBlend[ 8 ];
    extern unsigned int glOGLDepthCompare[ 8 ];
    extern unsigned int glOGLStencilCompare[ 8 ];
    extern unsigned int glOGLStencilOperation[ 6 ];
    extern unsigned int glOGLCullMode[ 3 ];
    extern unsigned int glOGLWireMode[ 2 ];

    extern unsigned int glOGLPrimitiveType[ 7 ];

    extern unsigned int glOGLAlphaCompare[ 8 ];
    extern unsigned int glOGLTextureTarget[ 5 ];
  }
}


#endif /* __MB_OPENGLMAPPING__ */
