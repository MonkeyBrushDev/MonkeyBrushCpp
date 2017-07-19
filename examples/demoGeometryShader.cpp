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

#include <iostream>
#include <string>

#include <mb/mb.h>
#include <routes.h>

#define MAXPOINTS 500		// Change this to increment num of points
#define RANDOM_POINT 0.02

std::vector< mb::Vector3 > createPoints( void )
{
  srand( time( NULL ) );
  std::vector< mb::Vector3 > points( MAXPOINTS );
  for ( int i = 0; i < MAXPOINTS; ++i )
  {
    points[ i ].x( ) = ( ( float ) ( std::rand( ) % 1000 ) ) * RANDOM_POINT;
    points[ i ].y( ) = ( ( float ) ( std::rand( ) % 1000 ) ) * RANDOM_POINT;
    points[ i ].z( ) = ( ( float ) ( std::rand( ) % 1000 ) ) * RANDOM_POINT;
  }

  return points;
}

std::shared_ptr<mb::Program> createProgram( std::shared_ptr<mb::Program> program )
{
  program->loadVertexShaderFromText( R"(
    #version 430
    layout (location = 0) in vec3 position;

    uniform mat4 MB_MATRIXM;
    uniform mat4 MB_MATRIXV;

    void main( )
    {
      gl_Position = MB_MATRIXV * MB_MATRIXM * vec4(position, 1.0);
    })" );
  program->loadGeometryShaderFromText( R"(
    #version 430
    layout (points) in;
    layout (line_strip, max_vertices = 64) out;

    uniform int uNumSides;
    uniform float uRadius;

    uniform mat4 MB_MATRIXP;

    #define PI 3.1415

    void main( )
    {
      for( int i = 0; i <= uNumSides; ++i )
      {
        float ang = PI * 2.0 / uNumSides * i;
        vec4 offset = vec4( cos(ang) * uRadius, -sin(ang) * uRadius, 0.0, 0.0 );
        gl_Position = MB_MATRIXP * (gl_in[0].gl_Position + offset);
        EmitVertex( );
      }
      EndPrimitive( );
    })" );
  program->loadFragmentShaderFromText( R"(
    #version 430
    out vec4 fragColor;

    void main( )
    {
		  fragColor = vec4( 1.0, 0.0, 1.0, 1.0 );
    })" );
  program->compileAndLink( );
  program->autocatching( );

  return program;
}

mb::Geometry* generateGeom( const mb::Color& )
{
  auto geom = new mb::Geometry( );

  geom->addPrimitive( new mb::PointPrimitive( createPoints( ) ) );

  mb::Material* customMaterial = new mb::Material( );
  customMaterial->program = createProgram( customMaterial->program );
  customMaterial->addUniform( MB_PROJ_MATRIX,
    std::make_shared< mb::Matrix4Uniform >( ) );
  customMaterial->addUniform( MB_VIEW_MATRIX,
    std::make_shared< mb::Matrix4Uniform >( ) );
  customMaterial->addUniform( MB_MODEL_MATRIX,
    std::make_shared< mb::Matrix4Uniform >( ) );
  customMaterial->addUniform( "uNumSides",
    std::make_shared< mb::IntegerUniform >( 32 ) );
  customMaterial->addUniform( "uRadius",
    std::make_shared< mb::FloatUniform >( 1.0f ) );

  customMaterial->state( ).wireframe( ).setEnabled( false );

  mb::MaterialComponent* mc = geom->getComponent<mb::MaterialComponent>( );
  mc->addMaterial( mb::MaterialPtr( customMaterial ) );

  return geom;
}

mb::Group* createScene( void )
{
  auto scene = new mb::Group( "scene" );

  auto camera = new mb::Camera( 60.0f, 500 / 500, 0.01f, 1000.0f );
  camera->local( ).translate( 0.0f, 0.0f, 25.0f );

  auto node = generateGeom( mb::Color::GREY );

  scene->addChild( node );

  camera->addComponent( new mb::FreeCameraComponent( ) );
  scene->addChild( camera );

  return scene;
}

int main( void )
{
  mb::FileSystem::getInstance( )->setBaseDirectory( MB_EXAMPLES_RESOURCES_ROUTE );

  mb::Window* window = new mb::GLFWWindow2( mb::WindowParams( 500, 500 ) );
  window->init( );
  window->setTitle( "Earth" );

  glEnable( GL_DEPTH_TEST );

  glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );

  glEnable( GL_DEPTH_TEST );

  mb::Application app;

  app.setSceneNode( createScene( ) );

  while ( window->isRunning( ) )
  {
    window->pollEvents( );

    if ( mb::Input::isKeyPressed( mb::Keyboard::Key::Esc ) )
    {
      window->close( );
      break;
    }

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    app.update( );

    window->swapBuffers( );
  }
  return 0;
}
