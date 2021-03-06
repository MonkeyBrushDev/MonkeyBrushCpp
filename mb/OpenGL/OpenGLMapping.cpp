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

#include "OpenGLMapping.hpp"

#include "../Includes.hpp"

namespace mb
{
  namespace gl
  {
    unsigned int glOGLSrcBlend[ 11 ] =
    {
      GL_ZERO,
      GL_ONE,
      GL_SRC_COLOR,
      GL_ONE_MINUS_SRC_COLOR,
      GL_DST_COLOR,
      GL_ONE_MINUS_DST_COLOR,
      GL_SRC_ALPHA,
      GL_ONE_MINUS_SRC_ALPHA,
      GL_DST_ALPHA,
      GL_ONE_MINUS_DST_ALPHA,
      GL_SRC_ALPHA_SATURATE
    };

    unsigned int glOGLDstBlend[ 8 ] =
    {
      GL_ZERO,
      GL_ONE,
      GL_SRC_COLOR,
      GL_ONE_MINUS_SRC_COLOR,
      GL_SRC_ALPHA,
      GL_ONE_MINUS_SRC_ALPHA,
      GL_DST_ALPHA,
      GL_ONE_MINUS_DST_ALPHA
    };

    unsigned int glOGLDepthCompare[ 8 ] =
    {
      GL_NEVER,
      GL_LESS,
      GL_EQUAL,
      GL_LEQUAL,
      GL_GREATER,
      GL_NOTEQUAL,
      GL_GEQUAL,
      GL_ALWAYS
    };

    unsigned int glOGLStencilCompare[ 8 ] =
    {
      GL_NEVER, GL_LESS, GL_EQUAL, GL_LEQUAL,
      GL_GREATER, GL_NOTEQUAL, GL_GEQUAL, GL_ALWAYS,
    };

    unsigned int glOGLStencilOperation[ 6 ] =
    {
      GL_KEEP, GL_ZERO, GL_REPLACE,
      GL_INCR, GL_DECR, GL_INVERT,
    };

    unsigned int glOGLCullMode[ 3 ] =
    {
      GL_FRONT,
      GL_BACK,
      GL_FRONT_AND_BACK
    };

    unsigned int glOGLWireMode[ 2 ] =
    {
      GL_LINE,
      GL_FILL
    };


    unsigned int glOGLPrimitiveType[ 7 ] =
    {
      GL_POINTS,
      GL_LINES,
      GL_LINE_LOOP,
      GL_LINE_STRIP,
      GL_TRIANGLES,
      GL_TRIANGLE_FAN,
      GL_TRIANGLE_STRIP
    };



    unsigned int glOGLAlphaCompare[ 8 ] =
    {
      GL_NEVER,
      GL_LESS,
      GL_EQUAL,
      GL_LEQUAL,
      GL_GREATER,
      GL_NOTEQUAL,
      GL_GEQUAL,
      GL_ALWAYS
    };

    unsigned int glOGLTextureTarget[ 5 ] =
    {
      GL_TEXTURE_1D,
      GL_TEXTURE_2D,
      GL_TEXTURE_2D_ARRAY,
      GL_TEXTURE_CUBE_MAP,
      GL_TEXTURE_3D,
    };
  }
}
