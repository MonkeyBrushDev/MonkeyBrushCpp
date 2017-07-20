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

int main( void )
{
  mb::FileSystem::getInstance( )->setBaseDirectory( MB_EXAMPLES_RESOURCES_ROUTE );
  mb::Window* window = new mb::GLFWWindow2( mb::WindowParams( 512, 512 ) );
  window->init( );

  mb::Program p;
  p.loadVertexShaderFromText( R"(
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
    })" );
  p.loadFragmentShaderFromText( R"(
    #version 330

    in vec3 color;
    out vec4 fragColor;

    void main( )
    {
      fragColor = vec4(color, 1.0);
    })" );
  p.create( );
  const char* varyings[ 2 ] = { "gl_Position", "color" };
  p.feedbackVarying( varyings, 2, GL_SEPARATE_ATTRIBS );
  p.link( );
  p.autocatching( );

  std::vector<mb::Vector4> positions = {
    mb::Vector4( -1.0f, -1.0f, 0.0f, 1.0f ),
    mb::Vector4( 1.0f, -1.0f, 0.0f, 1.0f ),
    mb::Vector4( 1.0f, 1.0f, 0.0f, 1.0f ),
    mb::Vector4( 1.0f, 1.0f, 0.0f, 1.0f ),
    mb::Vector4( -1.0f, 1.0f, 0.0f, 1.0f ),
    mb::Vector4( -1.0f, -1.0f, 0.0f, 1.0f )
  };
  unsigned int VERTEX_COUNT = positions.size( );

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
  mb::TransformFeedback ttf;
  ttf.bind( );
  glBindBufferBase( GL_TRANSFORM_FEEDBACK_BUFFER, 0, buffers[ 1 ] );
  glBindBufferBase( GL_TRANSFORM_FEEDBACK_BUFFER, 1, buffers[ 2 ] );
  ttf.unbind( );
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
  app.init( );

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
    p.use( );

    glBindVertexArray( VAOS[ 0 ] );
    ttf.bind( );

    ttf.beginTriangles( );
    glDrawArrays( GL_TRIANGLES, 0, VERTEX_COUNT );
    ttf.end( );
    ttf.unbind( );

    glDisable( GL_RASTERIZER_DISCARD );

    glBindBuffer( GL_ARRAY_BUFFER, buffers[ 1 ] );
    std::vector<mb::Vector4> arrBuffer = ttf.extractData<mb::Vector4>( positions.size( ) );

    glBindBuffer( GL_ARRAY_BUFFER, buffers[ 2 ] );
    std::vector<mb::Vector3> arrBuffer2 = ttf.extractData<mb::Vector3>( positions.size( ) );

    window->swapBuffers( );
  }

  return 0;
}
