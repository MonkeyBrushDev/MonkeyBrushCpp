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

#include <mb/mb.h>
#include <routes.h>
using namespace mb;

int main( )
{
  mb::FileSystem::getInstance( )->setBaseDirectory( MB_EXAMPLES_RESOURCES_ROUTE );

  mb::Window* window = new mb::GLFWWindow2( mb::WindowParams( 500, 500 ) );
  window->init( );

  auto scene = new Group( "scene" );

  mb::Material* customMaterial = new mb::UVMaterial( );
  auto geom = new Geometry( "nodeGeom" );
  geom->addPrimitive( new CubePrimitive( ) );
  mb::MaterialComponent* mc = geom->getComponent<mb::MaterialComponent>( );
  mc->addMaterial( mb::MaterialPtr( customMaterial ) );

  scene->addChild( geom );
  //geom->layer( ).set( 2 );

  auto camera = new mb::Camera( 45.0f, 500 / 500, 0.01f, 1000.0f );
  camera->local( ).translate( 0.0f, 0.0f, 10.0f );
  camera->addComponent( new mb::FreeCameraComponent( ) );

  camera->name( "PPCamera" );
  camera->renderPass( new PostRenderingPass( new StandardRenderingPass( ) ) );
  camera->renderPass( )->imageEffects( ).push_back( std::make_shared< SepiaToneEffect >( ) );
  //camera->renderPass( )->imageEffects( ).push_back( std::make_shared<  GreyToneEffect>( ) );
  scene->addChild( camera );

  //camera->layer( ).enable( 1 );
  //camera->layer( ).enable( 2 );
  //camera->layer( ).enable( 3 );

  glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );

  glEnable( GL_DEPTH_TEST );

  mb::Application app;

  app.setSceneNode( scene );

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
