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

#include "Sync.hpp"

namespace mb
{
  SyncRef Sync::create( GLenum condition, GLbitfield flags )
  {
    return std::make_shared< Sync >( condition, flags );
  }

  Sync::Sync( GLenum condition, GLbitfield flags )
  {
    _sync = glFenceSync( condition, flags );
  }

  Sync::~Sync( void )
  {
    glDeleteSync( _sync );
  }

  GLenum Sync::clientWaitSync( GLbitfield flags,
    GLuint64 timeoutNanoseconds )
  {
    return glClientWaitSync(
      _sync, flags, timeoutNanoseconds );
  }

  void Sync::waitSync( GLbitfield flags,
    GLuint64 timeoutNanoseconds )
  {
    glWaitSync( _sync, flags, timeoutNanoseconds );
  }
}
