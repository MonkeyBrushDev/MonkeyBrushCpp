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

#include "Query.hpp"

namespace mb
{
  Query::Query( void )
  {
    glCreateQueries( 1, 1, &_handler );
  }
  Query::~Query( void )
  {
    glDeleteQueries( 1, &_handler );
  }
  void Query::begin( unsigned int target )
  {
    glBeginQuery( target, _handler );
  }
  void Query::end( unsigned int target )
  {
    glEndQuery( target );
  }
  void Query::useAnySamples( const std::function<void( )>& cb )
  {
    oneUse( GL_ANY_SAMPLES_PASSED, cb );
  }
  void Query::useAnySamplesConservative( const std::function<void( )>& cb )
  {
    oneUse( GL_ANY_SAMPLES_PASSED_CONSERVATIVE, cb );
  }
  void Query::oneUse( unsigned int target, const std::function<void( )>& cb )
  {
    begin( target );
    cb( );
    end( target );
  }
  bool Query::isReady( void )
  {
    int value = 0;
    glGetQueryObjectiv( _handler, GL_QUERY_RESULT_AVAILABLE, &value );
    return value > 0;
  }
  GLint Query::getValueInt( void ) const
  {
    GLint value = 0;
    glGetQueryObjectiv( _handler, GL_QUERY_RESULT, &value );
    return value;
  }

  GLuint Query::getValueUInt( void ) const
  {
    GLuint value = 0;
    glGetQueryObjectuiv( _handler, GL_QUERY_RESULT, &value );
    return value;
  }

  GLint64 Query::getValueInt64( void ) const
  {
    GLint64 value = 0;
    glGetQueryObjecti64v( _handler, GL_QUERY_RESULT, &value );
    return value;
  }

  GLuint64 Query::getValueUInt64( void ) const
  {
    GLuint64 value = 0;
    glGetQueryObjectui64v( _handler, GL_QUERY_RESULT, &value );
    return value;
  }

  void Query::getValueInt( GLint* params ) const
  {
    glGetQueryObjectiv( _handler, GL_QUERY_RESULT, params );
  }

  void Query::getValueUInt( GLuint* params ) const
  {
    glGetQueryObjectuiv( _handler, GL_QUERY_RESULT, params );
  }

  void Query::getValueInt64( GLint64* params ) const
  {
    glGetQueryObjecti64v( _handler, GL_QUERY_RESULT, params );
  }

  void Query::getValueUInt64( GLuint64* params ) const
  {
    glGetQueryObjectui64v( _handler, GL_QUERY_RESULT, params );
  }
}
