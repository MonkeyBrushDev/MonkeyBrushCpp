#ifndef __NORMAL_FLIP_INCLUDED__
#define __NORMAL_FLIP_INCLUDED__

#ifdef DOUBLE_SIDED
  float flipNormal = ( float( gl_FrontFacing ) * 2.0 - 1.0 );
#else
  float flipNormal = 1.0;
#endif
normal = normalize( normal ) * flipNormal;

#endif
