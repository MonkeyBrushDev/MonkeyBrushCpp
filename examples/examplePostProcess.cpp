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

  mb::Material* customMaterial = new mb::NormalMaterial( );
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
#ifdef PP
  camera->renderPass( new mb::PostRenderingPass( new mb::StandardRenderingPass( ) ) );
  camera->renderPass( )->imageEffects( ).push_back( std::make_shared< mb::SepiaToneEffect >( ) );
#endif
  //camera->renderPass( )->imageEffects( ).push_back( std::make_shared<  GreyToneEffect>( ) );
  scene->addChild( camera );

  //camera->layer( ).enable( 1 );
  //camera->layer( ).enable( 2 );
  //camera->layer( ).enable( 3 );

  glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );

  glEnable( GL_DEPTH_TEST );

#ifndef PP
  unsigned int framebuffer;
  glGenFramebuffers( 1, &framebuffer );
  glBindFramebuffer( GL_FRAMEBUFFER, framebuffer );
  // create a color attachment texture
  unsigned int textureColorbuffer;
  glGenTextures( 1, &textureColorbuffer );
  glBindTexture( GL_TEXTURE_2D, textureColorbuffer );
  glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, 500, 500, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
  glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0 );
  // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
  unsigned int rbo;
  glGenRenderbuffers( 1, &rbo );
  glBindRenderbuffer( GL_RENDERBUFFER, rbo );
  glRenderbufferStorage( GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 500, 500 ); // use a single renderbuffer object for both a depth AND stencil buffer.
  glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo ); // now actually attach it
  // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
  if ( glCheckFramebufferStatus( GL_FRAMEBUFFER ) != GL_FRAMEBUFFER_COMPLETE )
    std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
  glBindFramebuffer( GL_FRAMEBUFFER, 0 );

  auto sepia = new mb::SepiaToneEffect( );
#endif

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


#ifdef PP
    app.update( );
#else
    glBindFramebuffer( GL_FRAMEBUFFER, framebuffer );
    app.update( );
    glBindFramebuffer( GL_FRAMEBUFFER, 0 );
    sepia->apply( app.renderer( ), mb::Camera::getMainCamera( ) );
#endif

    window->swapBuffers( );
  }
  return 0;
}
