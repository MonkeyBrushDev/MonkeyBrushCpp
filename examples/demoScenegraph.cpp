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

mb::Group* generateCubeGeom( const mb::Color& c )
{
  mb::Group* g = new mb::Group( "" );
  auto geom = new mb::Geometry( );

  geom->addPrimitive( new mb::CubePrimitive( ) );

  mb::BasicMaterial* customMaterial = new mb::BasicMaterial( );
  customMaterial->setColor( c );

  mb::MaterialComponent* mc = geom->getComponent<mb::MaterialComponent>( );
  mc->addMaterial( mb::MaterialPtr( customMaterial ) );

  geom->addComponent( new mb::RotateComponent( mb::Vector3::ONE, 0.25f ) );

  g->addChild( geom );
  return g;
}

mb::Group* generateSphereGeom( const mb::Color& c )
{
  mb::Group* g = new mb::Group( "" );
  auto geom = new mb::Geometry( );

  geom->addPrimitive( new mb::SpherePrimitive( ) );

  mb::BasicMaterial* customMaterial = new mb::BasicMaterial( );
  customMaterial->setColor( c );

  mb::MaterialComponent* mc = geom->getComponent<mb::MaterialComponent>( );
  mc->addMaterial( mb::MaterialPtr( customMaterial ) );

  geom->addComponent( new mb::RotateComponent( mb::Vector3::ONE, 0.25f ) );

  g->addChild( geom );
  return g;
}

mb::Group* createScene( void )
{
  auto scene = new mb::Group( "scene" );

  auto camera = new mb::Camera( 45.0f, 500 / 500, 0.01f, 1000.0f );
  camera->local( ).setPosition( 0.0f, 0.0f, 50.0f );

  auto base = generateSphereGeom( mb::Color::RED );
  base->local( ).setScale( 1.5f );

  for ( int i = -1; i < 2; i+= 2 )
  {
    auto cube = generateCubeGeom( mb::Color::GREY );
    cube->local( ).setPosition( mb::Vector3( 10.0f * i, 0.0f, 0.0f ) );
    for (unsigned int j = 0; j < 2; ++j )
    {
      auto sp = generateSphereGeom( mb::Color::BLUE );
      sp->local( ).setPosition( mb::Vector3( 0.0f, -5.0f * j, 0.0f ) );
      cube->addChild( sp );
    }
    base->addChild( cube );
  }

  scene->addChild( base );

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
  app.init( );

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
