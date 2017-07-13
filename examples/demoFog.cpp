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

  customMaterial->program = new mb::Program( );
  customMaterial->program->loadVertexShaderFromText( VS_FOG_SHADER );
  customMaterial->program->loadFragmentShaderFromText( FS_FOG_SHADER );
  customMaterial->program->compileAndLink( );
  customMaterial->program->autocatching( );

  customMaterial->addStandardUniforms( );
  customMaterial->addUniform( "density",
    std::make_shared< mb::FloatUniform >( 0.04f ) );

  return customMaterial;
}

mb::Geometry* generateGeom( const mb::Color& )
{
  auto geom = new mb::Geometry( );

  geom->addPrimitive( new mb::CubePrimitive( ) );

  mb::Material* customMaterial = createFogMaterial( );

  mb::MaterialComponent* mc = geom->getComponent<mb::MaterialComponent>( );
  mc->addMaterial( mb::MaterialPtr( customMaterial ) );

  geom->addComponent( new mb::RotateComponent( mb::Vector3::ONE, 0.25f ) );

  return geom;
}

mb::Group* createScene( void )
{
  auto scene = new mb::Group( "scene" );

  auto camera = new mb::Camera( 45.0f, 500 / 500, 0.01f, 1000.0f );
  camera->local( ).translate( 0.0f, 0.0f, 10.0f );

  scene->addChild( generateGeom( mb::Color::GREY ) );

  camera->addComponent( new mb::FreeCameraComponent( ) );
  scene->addChild( camera );

  return scene;
}

int main( )
{
  mb::FileSystem::getInstance( )->setBaseDirectory( MB_EXAMPLES_RESOURCES_ROUTE );

  mb::Window* window = new mb::GLFWWindow2( mb::WindowParams( 500, 500 ) );
  window->init( );
  window->setTitle( "Fog Demo" );

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

    app.update( );

    window->swapBuffers( );
  }
  return 0;
}
