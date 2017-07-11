/**
 * Copyright (c) 2017, Monkey Brush
 * All rights reserved.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

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
