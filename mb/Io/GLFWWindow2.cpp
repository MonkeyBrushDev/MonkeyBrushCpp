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

#include "../Exceptions/RuntimeException.hpp"

namespace mb
{
  bool GLFWWindow2::init( )
  {
	  mb::Log::debug("Initializing GLFW");

    if ( !glfwInit( ) )
    {
      throw RuntimeException( "Failed to initialise GLFW" );
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
      throw RuntimeException( "Failed to create window with GLFW." );
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

	  mb::Log::debug("GLFW initialized");

	  mb::Log::debug("Initializing GLEW");
    // Initialize GLEW to setup the OpenGL Function pointers
    glewExperimental = ( GLboolean ) true;
    if ( glewInit( ) != GLEW_OK )
    {
      glfwTerminate( );
      throw RuntimeException( "Failed to initialise GLEW" );
    }

  	mb::Log::debug("OpenGL functions succesfully loaded.");
  	mb::Log::debug("Version - Major: ", std::to_string(_params.maxVersion),
  		" Minor: ", std::to_string( _params.minVersion ));
  	mb::Log::debug("Driver: ", (char*)glGetString(GL_VENDOR),
  		" Renderer: ", (char*)glGetString(GL_RENDERER));

  	mb::Log::debug("GLEW initialized");

    Input::initialize( );
    mb::Log::debug("Input initialized");

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
  double calcFPS(mb::Window* window, std::string theWindowTitle = "Foo title",
    double theTimeInterval = 1.0 )
  {
    // Static values which only get initialised the first time the function runs
    static double t0Value       = glfwGetTime(); // Set the initial time to now
    static int    fpsFrameCount = 0;             // Set the initial FPS frame count to 0
    static double fps           = 0.0;           // Set the initial FPS value to 0.0

    // Get the current time in seconds since the program started (non-static, so executed every time)
    double currentTime = glfwGetTime();

    // Ensure the time interval between FPS checks is sane (low cap = 0.1s, high-cap = 10.0s)
    // Negative numbers are invalid, 10 fps checks per second at most, 1 every 10 secs at least.
    if (theTimeInterval < 0.1)
    {
      theTimeInterval = 0.1;
    }
    if (theTimeInterval > 10.0)
    {
      theTimeInterval = 10.0;
    }

    // Calculate and display the FPS every specified time interval
    if ((currentTime - t0Value) > theTimeInterval)
    {
      // Calculate the FPS as the number of frames divided by the interval in seconds
      fps = (double)fpsFrameCount / (currentTime - t0Value);

      // If the user specified a window title to append the FPS value to...
      if (theWindowTitle != "NONE")
      {
        // Convert the fps value into a string using an output stringstream
        std::ostringstream stream;
        stream << fps;
        std::string fpsString = stream.str();

        // Append the FPS value to the window title details
        theWindowTitle += " | FPS: " + fpsString;

        // Convert the new window title to a c_str and set it
        const char* pszConstString = theWindowTitle.c_str();
        window->setTitle(pszConstString);
      }
      else // If the user didn't specify a window to append the FPS to then output the FPS to the console
      {
        std::cout << "FPS: " << fps << std::endl;
      }

      // Reset the FPS frame counter and set the initial time to be now
      fpsFrameCount = 0;
      t0Value = glfwGetTime();
    }
    else // FPS calculation time interval hasn't elapsed yet? Simply increment the FPS frame counter
    {
      fpsFrameCount++;
    }

    // Return the current FPS - doesn't have to be used if you don't want it!
    return fps;
  }
  void GLFWWindow2::swapBuffers( )
  {
    calcFPS( this, _params.title);
    glfwSwapBuffers( _handle );
  }
}
