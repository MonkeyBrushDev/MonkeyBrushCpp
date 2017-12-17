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

  mb::Program p2;
  p2.loadVertexShaderFromText( R"(
    #version 330
    layout(location = 0) in vec4 position;
    layout(location = 1) in vec3 color;

    out vec3 v_color;

    void main( void )
    {
      gl_Position = position;
      v_color = color;
    })" );
  p2.loadFragmentShaderFromText( R"(
    #version 330

    in vec3 v_color;

    out vec4 fragColor;

    void main( void )
    {
      fragColor = vec4( v_color, 1.0 );
    }
  )" );
  p2.compileAndLink( );
  p2.autocatching( );

  std::vector<mb::Vector4> positions = {
    mb::Vector4( -1.0f, -1.0f, 0.0f, 1.0f ),
    mb::Vector4( 1.0f, -1.0f, 0.0f, 1.0f ),
    mb::Vector4( 1.0f, 1.0f, 0.0f, 1.0f ),
    mb::Vector4( 1.0f, 1.0f, 0.0f, 1.0f ),
    mb::Vector4( -1.0f, 1.0f, 0.0f, 1.0f ),
    mb::Vector4( -1.0f, -1.0f, 0.0f, 1.0f )
  };
  unsigned int VERTEX_COUNT = positions.size( );

  mb::Vbo buffer0( GL_ARRAY_BUFFER );
  mb::Vbo buffer1( GL_ARRAY_BUFFER );
  mb::Vbo buffer2( GL_ARRAY_BUFFER );

  // Transform buffer
  buffer0.bind( );
  buffer0.bufferData( sizeof( mb::Vector4 ) * positions.size( ), 
    positions.data( ), GL_STATIC_DRAW );

  // Feedback empty buffers
  buffer1.bind( );
  buffer1.bufferData( sizeof( mb::Vector4 ) * positions.size( ), 
    nullptr, GL_STATIC_READ );
  buffer1.unbind( );

  buffer2.bind( );
  buffer2.bufferData( sizeof( mb::Vector3 ) * positions.size( ), 
    nullptr, GL_STATIC_READ );
  buffer2.unbind( );


  GLuint VAOS[2];
  glCreateVertexArrays( 2, VAOS );
  glBindVertexArray( VAOS[ 0 ] );
  buffer0.bind( );
  glVertexAttribPointer( 0, 4, GL_FLOAT, GL_FALSE, 0, 0 );
  buffer0.unbind( );
  glEnableVertexAttribArray( 0 );
  glBindVertexArray( 0 );

  // Init transform
  mb::TransformFeedback ttf;
  ttf.bind( );
  ttf.setIndex( 0, &buffer1 );
  ttf.setIndex( 1, &buffer2 );
  ttf.unbind( );

  // Init feedback VAO
  glBindVertexArray( VAOS[ 1 ] );
  buffer1.bind( );
  glVertexAttribPointer( 0, 4, GL_FLOAT, false, 0, 0 );
  glEnableVertexAttribArray( 0 );

  buffer2.bind( );
  glVertexAttribPointer( 1, 3, GL_FLOAT, false, 0, 0 );
  glEnableVertexAttribArray( 1 );

  buffer2.unbind( );
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

    buffer1.bind( );
    std::vector<mb::Vector4> arrBuffer =
      ttf.extractData<mb::Vector4>( positions.size( ) );

    buffer2.bind( );
    std::vector<mb::Vector3> arrBuffer2 =
      ttf.extractData<mb::Vector3>( positions.size( ) );

    // Render
    p2.use( );
    glBindVertexArray( VAOS[ 1 ] );
    glDrawArrays( GL_TRIANGLES, 0, VERTEX_COUNT );
    glBindVertexArray( 0 );

    window->swapBuffers( );
  }

  return 0;
}
