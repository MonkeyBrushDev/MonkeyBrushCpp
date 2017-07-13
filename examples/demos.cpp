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

int main( )
{
  mb::FileSystem::getInstance( )->setBaseDirectory( MB_EXAMPLES_RESOURCES_ROUTE );
  mb::Window* window = new mb::GLFWWindow2( mb::WindowParams( 512, 512 ) );
  window->init( );

  // mb::Renderer* r = new mb::OpenGLRenderer( );

  const GLchar* vertexShaderSrc = R"(
    #version 330
    in float inValue;
    out float outValue;

    void main( )
    {
      outValue = sqrt( inValue );
    }
  )";

  const GLchar* feedbackVaryings[] = { "outValue" };
  mb::Program p;
  p.loadVertexShaderFromText( vertexShaderSrc );

  p.create( );
  p.feedbackVarying( feedbackVaryings, 1, GL_INTERLEAVED_ATTRIBS );
  p.link( );
  p.autocatching( );

  p.use( );

  mb::TransformFeedback ttf;

  // Create VAO
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // Create input VBO and vertex format
  GLfloat data[] = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f };

  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

  glEnableVertexAttribArray(p.attribute( "inValue" ) );
  glVertexAttribPointer(p.attribute( "inValue" ) , 1, GL_FLOAT, GL_FALSE, 0, 0);

  // Create transform feedback buffer
  GLuint tbo;
  glGenBuffers(1, &tbo);
  glBindBuffer(GL_ARRAY_BUFFER, tbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(data), nullptr, GL_STATIC_READ);

  // Perform feedback transform
  glEnable(GL_RASTERIZER_DISCARD);

  glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, tbo);

  glBeginTransformFeedback(GL_POINTS);
      glDrawArrays(GL_POINTS, 0, 5);
  glEndTransformFeedback();

  glDisable(GL_RASTERIZER_DISCARD);

  glFlush();

  // Fetch and print results
  GLfloat feedback[5];
  glGetBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER, 0, sizeof(feedback), feedback);

  printf("%f %f %f %f %f\n", feedback[0], feedback[1], feedback[2], feedback[3], feedback[4]);

  glDeleteBuffers(1, &tbo);
  glDeleteBuffers(1, &vbo);

  glDeleteVertexArrays(1, &vao);


  /*mb::Clock clockTime;
  clockTime.reset( );

  while ( window->isRunning( ) )
  {
    window->pollEvents( );

    if ( mb::Input::isKeyPressed( mb::Keyboard::Key::Esc ) )
    {
      window->close( );
      break;
    }

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    window->swapBuffers( );
  }*/

  return 0;
}
