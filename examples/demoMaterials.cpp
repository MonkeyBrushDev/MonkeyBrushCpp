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

#include "others/FogShader.hpp"

mb::Material* createFogMaterial( )
{
  mb::Material* customMaterial = new mb::Material( );

  customMaterial->program->loadVertexShaderFromText( VS_FOG_SHADER );
  customMaterial->program->loadFragmentShaderFromText( FS_FOG_SHADER );
  customMaterial->program->compileAndLink( );
  customMaterial->program->autocatching( );

  customMaterial->addStandardUniforms( );
  customMaterial->addUniform( "density",
    std::make_shared< mb::FloatUniform >( 0.04f ) );

  return customMaterial;
}

mb::Geometry* generateGeom( mb::Material* customMaterial )
{
  auto geom = new mb::Geometry( );

  geom->addPrimitive( new mb::SpherePrimitive( 1.0f, 25, 25 ) );

  mb::MaterialComponent* mc = geom->getComponent<mb::MaterialComponent>( );
  mc->addMaterial( mb::MaterialPtr( customMaterial ) );

  geom->addComponent( new mb::RotateComponent( mb::Vector3::ONE, 0.05f ) );

  return geom;
}

#include "others/AlienProceduralMaterial.hpp"
#include "others/GraniteProceduralMaterial.hpp"
#include "others/HatchingProceduralMaterial.hpp"
#include "others/MatCapMaterial.hpp"

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
    mb::Material* customMaterial = createFogMaterial( );
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
  window->setTitle( "Multi simple materials" );

  mb::Application app;

  app.setSceneNode( createScene( ) );

  app.init( ); // initialize settings to render the scene...

  while ( window->isRunning( ) )
  {
    window->pollEvents( );

    if ( mb::Input::isKeyPressed( mb::Keyboard::Key::Esc ) )
    {
      window->close( );
      break;
    }

    app.update( );

    window->swapBuffers( );
  }
  return 0;
}
