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

#include <mb/mb.h>
#include <routes.h>

GLuint createShader( const char* source, GLenum type )
{
  GLuint shader = glCreateShader( type );
  glShaderSource( shader, 1, &source, nullptr );
  glCompileShader( shader );
  int status;
  glGetShaderiv( shader, GL_COMPILE_STATUS, &status );
  if ( status == GL_FALSE )
  {
    int infoLogLength;
    glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &infoLogLength );
    GLchar* infoLog = new GLchar[ infoLogLength ];
    glGetShaderInfoLog( shader, infoLogLength, nullptr, infoLog );
    std::cout
      << "----------------------------- " << std::endl <<
      source << std::endl <<
      "----------------------------- " <<
      std::endl;
    std::cerr << "Compile log: " << infoLog << std::endl;
    delete[ ] infoLog;
    throw;
  }
  return shader;
}

int main( )
{
  mb::FileSystem::getInstance( )->setBaseDirectory( MB_EXAMPLES_RESOURCES_ROUTE );
  mb::Window* window = new mb::GLFWWindow2( mb::WindowParams( 512, 512 ) );
  window->init( );

  auto vShaderTransform = createShader( R"(
    #version 330
    layout(location = 0) in vec4 position;
    uniform mat4 MB_MATRIXM;
    uniform mat4 MB_MATRIXV;
    uniform mat4 MB_MATRIXP;
  
    out vec3 color;
    
    void main( )
    {
      mat4 mvp = mat4(
        0.5, 0.0, 0.0, 0.0,
        0.0, 0.5, 0.0, 0.0,
        0.0, 0.0, 0.5, 0.0,
        0.0, 0.0, 0.0, 1.0
      );
    
      gl_Position = mvp * position;
      gl_Position = position;
      color = vec3(clamp(vec2(position), 0.0, 1.0), 0.0);
    })", GL_VERTEX_SHADER );
  auto fShaderTransform = createShader( R"(
    #version 330

    in vec3 color;
    out vec4 fragColor;

    void main( )
    {
      fragColor = vec4(color, 1.0);
    })", GL_FRAGMENT_SHADER );
  auto programTransform = glCreateProgram( );
  glAttachShader( programTransform, vShaderTransform );
  glAttachShader( programTransform, fShaderTransform );
  const char* varyings [2] = { "gl_Position", "color" };
  glTransformFeedbackVaryings( programTransform, 2, varyings, GL_SEPARATE_ATTRIBS );
  glLinkProgram( programTransform );

  int VERTEX_COUNT = 6;
  std::vector<mb::Vector4> positions = {
    mb::Vector4( -1.0f, -1.0f, 0.0f, 1.0f ),
    mb::Vector4( 1.0f, -1.0f, 0.0f, 1.0f ),
    mb::Vector4( 1.0f, 1.0f, 0.0f, 1.0f ),
    mb::Vector4( 1.0f, 1.0f, 0.0f, 1.0f ),
    mb::Vector4( -1.0f, 1.0f, 0.0f, 1.0f ),
    mb::Vector4( -1.0f, -1.0f, 0.0f, 1.0f )
  };

  GLuint buffers[ 3 ];
  glCreateBuffers( 3, buffers );

  // Transform buffer
  glBindBuffer( GL_ARRAY_BUFFER, buffers[ 0 ] );
  glBufferData( GL_ARRAY_BUFFER, sizeof( mb::Vector4 ) * positions.size( ), 
    positions.data( ), GL_STATIC_DRAW );

  // Feedback empty buffers
  glBindBuffer( GL_ARRAY_BUFFER, buffers[ 1 ] );
  glBufferData( GL_ARRAY_BUFFER, positions.size( ) * sizeof( mb::Vector4 ), nullptr, GL_STATIC_COPY );
  glBindBuffer( GL_ARRAY_BUFFER, 0 );

  glBindBuffer( GL_ARRAY_BUFFER, buffers[ 2 ] );
  glBufferData( GL_ARRAY_BUFFER, positions.size( ) * sizeof( mb::Vector3 ), nullptr, GL_STATIC_COPY );
  glBindBuffer( GL_ARRAY_BUFFER, 0 );


  GLuint VAOS[2];
  glCreateVertexArrays( 2, VAOS );
  glBindVertexArray( VAOS[ 0 ] );
  glBindBuffer( GL_ARRAY_BUFFER, buffers[ 0 ] );
  glVertexAttribPointer( 0, 4, GL_FLOAT, GL_FALSE, 0, 0 );
  glBindBuffer( GL_ARRAY_BUFFER, 0 );
  glEnableVertexAttribArray( 0 );
  glBindVertexArray( 0 );

  // Init transform
  GLuint tf;
  glCreateTransformFeedbacks( 1, &tf );
  glBindTransformFeedback( GL_TRANSFORM_FEEDBACK, tf );
  glBindBufferBase( GL_TRANSFORM_FEEDBACK_BUFFER, 0, buffers[ 1 ] );
  glBindBufferBase( GL_TRANSFORM_FEEDBACK_BUFFER, 1, buffers[ 2 ] );
  glBindTransformFeedback( GL_TRANSFORM_FEEDBACK, 0 );
  glBindBufferBase( GL_TRANSFORM_FEEDBACK_BUFFER, 0, 0 );
  glBindBufferBase( GL_TRANSFORM_FEEDBACK_BUFFER, 1, 0 );

  // Init feedback VAO
  glBindVertexArray( VAOS[ 1 ] );
  GLuint vertexPosLocationFeedback = 0; // set with GLSL layout qualifier
  glBindBuffer( GL_ARRAY_BUFFER, buffers[ 1 ] );
  glVertexAttribPointer( vertexPosLocationFeedback, 4, GL_FLOAT, false, 0, 0 );
  glEnableVertexAttribArray( vertexPosLocationFeedback );

  GLuint vertexColorLocationFeedback = 3; // set with GLSL layout qualifier
  glBindBuffer( GL_ARRAY_BUFFER, buffers[ 2 ] );
  glVertexAttribPointer( vertexColorLocationFeedback, 3, GL_FLOAT, false, 0, 0 );
  glEnableVertexAttribArray( vertexColorLocationFeedback );

  glBindBuffer( GL_ARRAY_BUFFER, 0 );
  glBindVertexArray( 0 );


  mb::Application app;
  app.setSceneNode( new mb::Group( "" ) );

  while ( window->isRunning( ) )
  {
    window->pollEvents( );

    if ( mb::Input::isKeyPressed( mb::Keyboard::Key::Esc ) )
    {
      window->close( );
      break;
    }

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glEnable( GL_RASTERIZER_DISCARD );
    glUseProgram( programTransform );

    glBindVertexArray( VAOS[ 0 ] );
    glBindTransformFeedback( GL_TRANSFORM_FEEDBACK, tf );

    glBeginTransformFeedback( GL_TRIANGLES );
    glDrawArraysInstanced( GL_TRIANGLES, 0, VERTEX_COUNT, 1 );
    glEndTransformFeedback( );
    glBindTransformFeedback( GL_TRANSFORM_FEEDBACK, 0 );

    glDisable( GL_RASTERIZER_DISCARD );

    std::vector<mb::Vector4> arrBuffer( positions.size( ) );
    std::vector<mb::Vector3> arrBuffer2( positions.size( ) );
    
    //std::vector<float> arrBuffer( positions.size( ) * sizeof( mb::Vector4 ) );
    //std::vector<float> arrBuffer2( positions.size( ) * sizeof( mb::Vector3 ) );
    glBindBuffer( GL_ARRAY_BUFFER, buffers[ 1 ] );
    glGetBufferSubData( GL_ARRAY_BUFFER, 0, sizeof( mb::Vector4 ) * positions.size( ),
      arrBuffer.data( ) );
    glBindBuffer( GL_ARRAY_BUFFER, buffers[ 2 ] );
    glGetBufferSubData( GL_ARRAY_BUFFER, 0, sizeof( mb::Vector3 ) * positions.size( ),
      arrBuffer2.data( ) );
    
    //glBufferData( )

    window->swapBuffers( );
  }

  return 0;
}