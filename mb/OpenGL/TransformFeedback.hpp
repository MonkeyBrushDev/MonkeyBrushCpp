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

#ifndef __MB__TRANSFORM_FEEDBACK__
#define __MB__TRANSFORM_FEEDBACK__

#include <mb/api.h>
#include "Program.hpp"
#include <vector>

#include <GL/glew.h>

namespace mb
{
  class TransformFeedback
  {
  public:
    MB_API
    TransformFeedback( void );
    MB_API
    virtual ~TransformFeedback( void );
    /**
    * Bind this TransformFeedback object to current GL state.
    */
    MB_API
    void bind( void );
    /**
    * Unbind this TransformFeedback object to current GL state.
    */
    MB_API
    void unbind( void );
    /**
    * Init TransformFeedback operation using given mode.
    * @param {MB.ctes.TFPrimitive} mode TransformFeedback mode.
    */
    MB_API
    void begin(unsigned int mode);
    /**
    * Init TransformFeedback operation using point mode.
    */
    MB_API
    void beginPoints( void );
    /**
    * Init TransformFeedback operation using line mode.
    */
    MB_API
    void beginLines( void );
    /**
    * Init TransformFeedback operation using triangle mode.
    */
    MB_API
    void beginTriangles( void );
    /**
    * Finish TransformFeedback operation.
    */
    MB_API
    void end( void );
    /**
    * Pause TransformFeedback operation.
    */
    MB_API
    void pause( void );
    /**
    * Resume TransformFeedback operation.
    */
    MB_API
    void resume( void );
    MB_API
    static void varyings(const mb::Program* prog,
      const std::vector<const char*>& varyings, unsigned int bufferMode);

    template<typename T>
    std::vector<T> extractData(unsigned int numElems) const
    {
      std::vector< T > arrBuffer( numElems );
      glGetBufferSubData( GL_ARRAY_BUFFER, 0, sizeof( T ) * numElems, arrBuffer.data( ) );
      return arrBuffer;
    }

    MB_API
    inline unsigned int handler( void ) const
    {
      return _handler;
    }
  //protected:
    unsigned int _handler;
  };
}

#endif /* __MB__TRANSFORM_FEEDBACK__ */
