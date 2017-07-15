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

#ifndef __MB_SYNC__
#define __MB_SYNC__

#include "../Includes.hpp"
#include <functional>

namespace mb
{
  typedef std::shared_ptr<class Sync> SyncRef;
  class Sync
  {
  public:
    MB_API
    static SyncRef create(
      GLenum condition = GL_SYNC_GPU_COMMANDS_COMPLETE,
      GLbitfield flags = 0
    );
    MB_API
    ~Sync( void );
    MB_API
    GLenum clientWaitSync(
      GLbitfield flags = GL_SYNC_FLUSH_COMMANDS_BIT,
      GLuint64 timeoutNanoseconds = 0
    );
    MB_API
    void waitSync( GLbitfield flags = 0,
      GLuint64 timeout = GL_TIMEOUT_IGNORED );
    GLsync getObject( void ) { return _sync; }

    Sync( GLenum condition, GLbitfield flags );
  protected:
    GLsync _sync;
  };
}

#endif /* __MB_SYNC__ */
