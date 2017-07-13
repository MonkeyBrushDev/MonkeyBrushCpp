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

class RotationComponent : public mb::Component
{
  IMPLEMENT_COMPONENT( RotationComponent )
public:
  RotationComponent( float speed )
    : _speed( speed )
    , _time( 0.0f )
  { }
  virtual void update( const mb::Clock& clock )
  {
    node( )->local( ).rotate( ).fromAxisAngle(
      mb::Vector3::ONE, _time * mb::Mathf::TWO_PI );
    _time += _speed *clock.getDeltaTime( );
  }
protected:
  float _speed;
  float _time;
};

mb::Group* createScene( const std::string& objFile, const std::string& /*texFile*/ )
{
  auto scene = new mb::Group( "scene" );

  auto camera = new mb::Camera( 75.0f, 500 / 500, 0.03f, 1000.0f );
  camera->local( ).translate( 0.0f, 10.0f, 50.0f );

  camera->addComponent( new mb::FreeCameraComponent( ) );
  scene->addChild( camera );


  // LOAD MODEL
  auto geom = new mb::Geometry( );
  geom->addPrimitive( new mb::MeshPrimitive( objFile ) );

  /*mb::Texture2D* diffuse = mb::Texture2D::loadFromImage( texFile );

  mb::ColorMaterial* customMaterial = new mb::ColorMaterial( );
  customMaterial->setColor( mb::Color::WHITE );
  customMaterial->setColorMap( diffuse );*/

  mb::FlatColorMaterial* customMaterial = new mb::FlatColorMaterial( );
  customMaterial->setColor( mb::Color::YELLOW );

  customMaterial->state( ).wireframe( ).setEnabled( true );
  customMaterial->state( ).culling( ).setEnabled( false );

  geom->local( ).setScale( 0.5f );

  mb::MaterialComponent* mc = geom->getComponent<mb::MaterialComponent>( );
  mc->addMaterial( mb::MaterialPtr( customMaterial ) );

  //geom->addComponent( new mb::RotateComponent( mb::Vector3::ONE, 0.25f ) );

  scene->addChild( geom );

  return scene;
}

int main( int argc, char* argv[] )
{
  mb::FileSystem::getInstance( )->setBaseDirectory( MB_EXAMPLES_RESOURCES_ROUTE );

  mb::Window* window = new mb::GLFWWindow2( mb::WindowParams( 500, 500 ) );
  window->init( );
  window->setTitle( "Model loader" );

  mb::Application app;

  std::string objFile;
  std::string textureFile;
  if ( argc >= 3 )
  {
    objFile = std::string( argv[ 1 ] );
    textureFile = std::string( argv[ 2 ] );
  }
  else
  {
    objFile = std::string( "objects/Pikachu/pikachu.obj_" );
    textureFile = std::string( "objects/Pikachu/pikachu.png" );
  }

  app.setSceneNode( createScene( objFile, textureFile ) );

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
