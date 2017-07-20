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
      mb::Vector3::Y_AXIS, _time * mb::Mathf::TWO_PI );
    _time += _speed *clock.getDeltaTime( );
  }
protected:
  float _speed;
  float _time;
};

class Astro: public mb::Group
{
public:
  mb::Group* tgDis;
  mb::Geometry* sphere;
  Astro( float radius, const std::string& texture, float distance,
    float velRotOrb, float velRot, const mb::Color& )
    : Group( "Astro" )
  {
    sphere = new mb::Geometry( );
    sphere->addPrimitive( new mb::SpherePrimitive( 1.0f, 25, 25 ) );
    sphere->local( ).setPosition( mb::Vector3::ZERO );
    sphere->local( ).setScale( radius );

    mb::Texture2D* planetDiffuse = mb::Texture2D::loadFromImage( texture );

    mb::ColorMaterial* customMaterial = new mb::ColorMaterial( );
    customMaterial->setColorMap( planetDiffuse );
    customMaterial->setColor( mb::Color::WHITE );

    mb::MaterialComponent* mc = sphere->getComponent<mb::MaterialComponent>( );
    mc->addMaterial( mb::MaterialPtr( customMaterial ) );

    auto tgRotOrb = new mb::Group( "tgRotOrb" );
    tgDis = new mb::Group( "tgDis" );
    auto tgRot = new mb::Group( "tgRot" );

    tgRot->addChild( sphere );
    tgDis->addChild( tgRot );
    tgRotOrb->addChild( tgDis );
    this->addChild( tgRotOrb );

    tgRotOrb->addComponent( new RotationComponent( velRotOrb * 10.0f ) );
    tgRot->addComponent( new RotationComponent( velRot * 10.0f ) );

    mb::Vector3 pos = this->tgDis->local( ).getPosition( );

    this->tgDis->local( ).setPosition( distance, pos.y(), pos.z() );
  }
  void addSatelite( mb::Group* s )
  {
    this->tgDis->addChild( s );
  }
};

mb::Group* createScene( void )
{
  auto scene = new mb::Group( "scene" );

  auto camera = new mb::Camera( 45.0f, 500 / 500, 0.01f, 1000.0f );
  camera->local( ).translate( 0.0f, 0.0f, 20.0f );

  auto sun = new Astro( 6.0f / 2.0f, "sun.png", 0.0f, 0.0f, 0.002f, mb::Color::YELLOW );
  auto earth = new Astro( 1.27f / 2.0f, "earth.png", 6.0f, 0.001f, 0.005f, mb::Color::BLUE );
  auto moon = new Astro( 0.34f / 2.0f, "moon.png", 1.0f, 0.01f, 0.0f, mb::Color::WHITE );

  scene->addChild( sun );
  sun->addSatelite( earth );
  earth->addSatelite( moon );

  camera->addComponent( new mb::FreeCameraComponent( ) );
  scene->addChild( camera );

  return scene;
}

int main( )
{
  mb::FileSystem::getInstance( )->setBaseDirectory( MB_EXAMPLES_RESOURCES_ROUTE );

  mb::Window* window = new mb::GLFWWindow2( mb::WindowParams( 500, 500 ) );
  window->init( );
  window->setTitle( "Solar System" );

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
