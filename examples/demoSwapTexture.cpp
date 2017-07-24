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

class SwapTextureController : public mb::Component
{
  IMPLEMENT_COMPONENT( SwapTextureController )
public:
  SwapTextureController( void )
    : mb::Component( )
    , _counter( 1.0f )
  {
      mb::Texture2D* Tex1 = mb::Texture2D::loadFromImage( "green_matcap.jpg" );
      mb::Texture2D* Tex2 = mb::Texture2D::loadFromImage( "rubymatcap.jpg" );
      cpp = new mb::CustomPingPong< mb::Texture *>( Tex1, Tex2 );
  }
  virtual void start( void ) override
  {
    _material = node( )->getComponent< mb::MaterialComponent >( )->first( );
    _material->uniform( "DiffuseTexture" )->value( cpp->first( ) );
  }
  virtual void update( const mb::Clock& clock ) override
  {
    _counter -= clock.getDeltaTime( );
    if ( _counter < 0.0f )
    {
      cpp->swap( );
      _material->uniform( "DiffuseTexture" )->value( cpp->first( ) );
      _counter = 1.0f;
    }
  }
protected:
  float _counter;
  mb::CustomPingPong< mb::Texture *>* cpp;
  mb::MaterialPtr _material;
};

mb::Geometry* generateGeom( const mb::Color& )
{
  auto geom = new mb::Geometry( );

  geom->addPrimitive( new mb::CubePrimitive( 5.0f ) );

  mb::ColorMaterial* customMaterial = new mb::ColorMaterial( );
  customMaterial->setColor( mb::Color::WHITE );

  mb::MaterialComponent* mc = geom->getComponent<mb::MaterialComponent>( );
  mc->addMaterial( mb::MaterialPtr( customMaterial ) );

  geom->addComponent( new mb::RotateComponent( mb::Vector3::Y_AXIS, 0.15f ) );

  geom->addComponent( new SwapTextureController( ) );

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
  window->setTitle( "Swap texture Demo" );

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
