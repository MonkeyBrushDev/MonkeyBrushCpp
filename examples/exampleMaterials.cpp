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

mb::Program* createProgram( )
{
  mb::Program* program = new mb::Program( );
  program->loadVertexShaderFromText( R"(
    #version 330 core
    layout (location = 0) in vec3 Vertex;

    uniform mat4 mb_MatrixM;
    uniform mat4 mb_MatrixV;
    uniform mat4 mb_MatrixP;

    out vec3 position;

    void main()
    {
      gl_Position = mb_MatrixP * mb_MatrixV * mb_MatrixM * vec4(Vertex, 1.0);
      position = vec3( mb_MatrixV * mb_MatrixM * vec4( Vertex, 1.0 ) );
    })" );
  program->loadFragmentShaderFromText( R"(
    #version 330 core
    in vec3 position;
    out vec4 fragColor;

    uniform float density;
    uniform mat4 mb_MatrixV;

    const vec3 fogColor = vec3( 0.2, 0.3, 0.3 );
    const vec3 color = vec3( 1.0, 0.3, 0.4 );

    void main()
    {
      vec3 viewPos = -transpose(mat3(mb_MatrixV)) * mb_MatrixV[3].xyz;
      float dst = length(position - viewPos);
      float fogFactor = 1.0 / exp(dst * density);
      fogFactor = clamp(fogFactor, 0.0, 1.0);
      fragColor = vec4(mix(fogColor, color, fogFactor), 1.0);
    })" );
  program->compileAndLink( );
  program->autocatching( );

  return program;
}

mb::Geometry* generateGeom( mb::Material* customMaterial )
{
  auto geom = new mb::Geometry( );

  geom->addPrimitive( new mb::IcosahedronPrimitive( ) ); // ( 1.0f, 25, 25 ) );

  mb::MaterialComponent* mc = geom->getComponent<mb::MaterialComponent>( );
  mc->addMaterial( mb::MaterialPtr( customMaterial ) );

  geom->addComponent( new mb::RotateComponent( mb::Vector3::ONE, 0.05f ) );

  return geom;
}

#include "AlienProceduralMaterial.hpp"
#include "GraniteProceduralMaterial.hpp"
#include "HatchingProceduralMaterial.hpp"
#include "MatCapMaterial.hpp"

mb::Group* createScene( void )
{
  auto scene = new mb::Group( "scene" );

  auto camera = new mb::Camera( 45.0f, 500 / 500, 0.01f, 1000.0f );
  camera->local( ).translate( 0.0f, 0.0f, 10.0f );


  std::vector<mb::Vector3> positions = {
    mb::Vector3( -3.0f, 0.0f, -3.0f ),
    mb::Vector3( 0.0f, 0.0f, -3.0f ),
    mb::Vector3( 3.0f, 0.0f, -3.0f ),

    mb::Vector3( -3.0f, 0.0f, 0.0f),
    mb::Vector3( 0.0f, 0.0f, 0.0f ),
    mb::Vector3( 3.0f, 0.0f, 0.0f ),

    mb::Vector3( -3.0f, 0.0f, 3.0f ),
    mb::Vector3( 0.0f, 0.0f, 3.0f ),
    mb::Vector3( 3.0f, 0.0f, 3.0f ),
  };
  uint32_t index = 0;
  {
    mb::Material* customMaterial = new mb::Material( );
    customMaterial->program = createProgram( );
    customMaterial->addUniform( MB_PROJ_MATRIX,
      std::make_shared< mb::Matrix4Uniform >( ) );
    customMaterial->addUniform( MB_VIEW_MATRIX,
      std::make_shared< mb::Matrix4Uniform >( ) );
    customMaterial->addUniform( MB_MODEL_MATRIX,
      std::make_shared< mb::Matrix4Uniform >( ) );
    customMaterial->addUniform( "density",
      std::make_shared< mb::FloatUniform >( 0.04f ) );
    auto node = generateGeom( customMaterial );
    scene->addChild( node );

    node->local( ).setPosition( positions[ index++ ] );
  }
  {
    mb::Material* customMaterial = new mb::UVMaterial( );
    auto node = generateGeom( customMaterial );
    scene->addChild( node );

    node->local( ).setPosition( positions[ index++ ] );
  }
  {
    mb::BasicMaterial* customMaterial = new mb::BasicMaterial( );
    customMaterial->setColor( mb::Color::BLUE );
    auto node = generateGeom( customMaterial );
    scene->addChild( node );

    node->local( ).setPosition( positions[ index++ ] );
  }
  {
    mb::Material* customMaterial = new mb::NormalMaterial( );
    auto node = generateGeom( customMaterial );
    scene->addChild( node );

    node->local( ).setPosition( positions[ index++ ] );
  }
  {
    mb::Material* customMaterial = new mb::NormalMaterial( true );
    auto node = generateGeom( customMaterial );
    scene->addChild( node );

    node->local( ).setPosition( positions[ index++ ] );
  }
  {
    mb::Material* customMaterial = new GraniteProceduralMaterial( );
    auto node = generateGeom( customMaterial );
    scene->addChild( node );

    node->local( ).setPosition( positions[ index++ ] );
  }
  {
    mb::Material* customMaterial = new HatchingProceduralMaterial( );
    auto node = generateGeom( customMaterial );
    scene->addChild( node );

    node->local( ).setPosition( positions[ index++ ] );
  }
  {
    mb::Material* customMaterial = new AlienProceduralMaterial( );
    auto node = generateGeom( customMaterial );
    scene->addChild( node );

    node->local( ).setPosition( positions[ index++ ] );
  }
  {
    MatCapMaterial* customMaterial = new MatCapMaterial( );
    mb::Texture2D* MatCapDiffuse = mb::Texture2D::loadFromImage( "rubymatcap.jpg" );
    customMaterial->setMatcapMap( MatCapDiffuse );
    auto node = generateGeom( customMaterial );
    scene->addChild( node );

    node->local( ).setPosition( positions[ index++ ] );
  }

  camera->addComponent( new mb::FreeCameraComponent( ) );
  scene->addChild( camera );

  return scene;
}



int main( )
{
  mb::FileSystem::getInstance( )->setBaseDirectory( MB_EXAMPLES_RESOURCES_ROUTE );

  mb::Window* window = new mb::GLFWWindow2( mb::WindowParams( 500, 500 ) );
  window->init( );

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
