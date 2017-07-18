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

#ifndef __MB_QUERY__
#define __MB_QUERY__

#include "../Includes.hpp"
#include <functional>

namespace mb
{
  class Query
  {
  public:
    MB_API
    Query( void );
    MB_API
    virtual ~Query( void );
    MB_API
    void begin( unsigned int target );
    MB_API
    void end( unsigned int target );
    MB_API
    void useAnySamples( const std::function<void( )>& cb );
    MB_API
    void useAnySamplesConservative( const std::function<void( )>& cb );
    MB_API
    void oneUse( unsigned int target, const std::function<void( )>& cb );
    MB_API
    bool isReady( void );
    MB_API
    GLint getValueInt( void ) const;
    MB_API
    GLuint getValueUInt( void ) const;
    MB_API
    GLint64 getValueInt64( void ) const;
    MB_API
    GLuint64 getValueUInt64( void ) const;

    MB_API
    void getValueInt( GLint* params ) const;
    MB_API
    void getValueUInt( GLuint* params ) const;
    MB_API
    void getValueInt64( GLint64* params ) const;
    MB_API
    void getValueUInt64( GLuint64* params ) const;
  protected:
    unsigned int _handler;
  };
}

#endif /* __MB_QUERY__ */
