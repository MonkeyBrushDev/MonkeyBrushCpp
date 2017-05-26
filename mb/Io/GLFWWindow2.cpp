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

#include "GLFWWindow2.hpp"
#include "Input.hpp"
#include <string>

namespace mb
{
  bool GLFWWindow2::init( )
  {
	mb::Log::info("Initializing GLFW");
    if ( !glfwInit( ) )
    {
      throw "Failed to initialise GLFW";
    }
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, _params.maxVersion );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, _params.minVersion );
    glfwWindowHint( GLFW_SAMPLES, ( int ) _params.multiSample );
    glfwWindowHint( GLFW_DEPTH_BITS, ( int ) _params.depthBufferBit );
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint( GLFW_RESIZABLE, _params.resizable );

    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE );


    this->_handle = glfwCreateWindow( _params.width, _params.height, _params.title, nullptr, nullptr );

    if ( _handle == nullptr )
    {
      glfwTerminate( );
      throw "Failed to create window with GLFW.";
    }

    glfwSetKeyCallback( _handle, []( GLFWwindow*, int key, int, int act, int )
    {
      if ( act == GLFW_PRESS )
      {
        static_cast<GLFWKeyboard*>( Input::Keyboard( ) )->onKeyDown( key );
      }
      else if ( act == GLFW_RELEASE )
      {
        static_cast<GLFWKeyboard*>( Input::Keyboard( ) )->onKeyUp( key );
      }
    } );

    glfwSetCursorPosCallback( _handle, []( GLFWwindow*, double xpos, double ypos )
    {
      static_cast<GLFWMouse*>( Input::Mouse( ) )->onMouseMove( static_cast<int>( xpos ), static_cast<int>( ypos ) );
    } );

    glfwSetMouseButtonCallback( _handle, []( GLFWwindow*, int btn, int act, int )
    {
      static_cast<GLFWMouse*>( Input::Mouse( ) )->onMouseButtonEvent( btn, act );
    } );

    glfwSetScrollCallback( _handle, []( GLFWwindow*, double xoffset, double yoffset )
    {
      static_cast<GLFWMouse*>( Input::Mouse( ) )->onMouseWheelEvent( static_cast<int>( xoffset ), static_cast<int>( yoffset ) );
    } );

    glfwSetWindowSizeCallback( _handle, ( []( GLFWwindow* /*window*/, int width, int height )
    {
      glViewport( 0, 0, width, height );
      // TODO: Send event and set width and height from _params
    } ) );

    glfwSetInputMode( _handle, GLFW_STICKY_KEYS, GL_TRUE );
    glfwMakeContextCurrent( _handle );

	mb::Log::info("GLFW initialized");


	mb::Log::info("Initializing GLEW");
    // Initialize GLEW to setup the OpenGL Function pointers
    glewExperimental = ( GLboolean ) true;
    if ( glewInit( ) != GLEW_OK )
    {
      glfwTerminate( );
      throw "Failed to initialise GLEW";
    }

	mb::Log::info("OpenGL functions succesfully loaded.");
	mb::Log::info("Version - Major: ", std::to_string(_params.maxVersion),
		" Minor: ", std::to_string( _params.minVersion ));
	mb::Log::info("Driver: ", (char*)glGetString(GL_VENDOR),
		" Renderer: ", (char*)glGetString(GL_RENDERER));

	mb::Log::info("GLEW initialized");

    return true;
  }
  void* GLFWWindow2::getWindow( )
  {
    return this->_handle;
  }
  GLFWWindow2::GLFWWindow2( const WindowParams& params )
    : mb::Window( params )
  {
    _handle = nullptr;
  }
  GLFWWindow2::~GLFWWindow2( )
  {
    glfwTerminate( );
  }
  void GLFWWindow2::setTitle( const char* title )
  {
    glfwSetWindowTitle( _handle, title );
  }
  bool GLFWWindow2::isRunning( )
  {
    return glfwWindowShouldClose( _handle ) == 0;
  }
  void GLFWWindow2::pollEvents( )
  {
    glfwPollEvents( );
  }
  void GLFWWindow2::close( )
  {
    glfwTerminate( );
  }
  void GLFWWindow2::swapBuffers( )
  {
    glfwSwapBuffers( _handle );
  }
}
