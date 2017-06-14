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

#pragma once

#include "../Rendering/FramebufferObject.hpp"

#include "../Includes.hpp"

namespace mb
{
  namespace gl
  {
    class FBOResource
    {
    public:
      FBOResource( )
      {
        glGenFramebuffers( 1, &_handler );
      }
      virtual ~FBOResource( void ) { }
      virtual void bind( FramebufferObject* fbo )
      {
        glBindFramebuffer( GL_FRAMEBUFFER, _handler );
        glViewport( 0.0f, 0.0f, fbo->getWidth( ), fbo->getHeight( ) );

        const Color4& clearColor = fbo->getClearColor( );

        glClearColor( clearColor.r( ), clearColor.g( ), clearColor.b( ), clearColor.a( ) );
      }
      virtual void unbind( FramebufferObject* )
      {
        glBindFramebuffer( GL_FRAMEBUFFER, 0 );
      }
      virtual void load( FramebufferObject* )
      {

      }
      virtual void unload( FramebufferObject* )
      {

      }
      virtual void cleanup( void )
      {
        // TODO: Destroy textures
        glDeleteFramebuffers( 1, &_handler );
      }
    protected:
      unsigned int _handler;
    };
  }
}
