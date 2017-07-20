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

// TODO: ADD SPECULAR AND NORMAL TEXTURE TO EARTH

mb::Geometry* generateGeom( const mb::Color& c, const std::string& tex )
{
  auto geom = new mb::Geometry( );
//  geom->addPrimitive( new mb::SpherePrimitive( 5.0f, 100, 50 ) );
  geom->addPrimitive( new mb::TorusPrimitive(  ) );


  mb::ColorMaterial* customMaterial = new mb::ColorMaterial( );
  customMaterial->setColor( c );

  mb::Texture2D* TexDiffuse = mb::Texture2D::loadFromImage( tex );
  customMaterial->setColorMap( TexDiffuse );

  mb::MaterialComponent* mc = geom->getComponent<mb::MaterialComponent>( );
  mc->addMaterial( mb::MaterialPtr( customMaterial ) );

  //geom->addComponent( new mb::RotateComponent( mb::Vector3::ONE, 0.15f ) );

  return geom;
}

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

mb::Group* createScene( void )
{
  auto scene = new mb::Group( "scene" );

  auto camera = new mb::Camera( 60.0f, 500 / 500, 0.01f, 1000.0f );
  camera->local( ).translate( 0.0f, 0.0f, 25.0f );
  camera->addComponent( new mb::FreeCameraComponent( ) );
  scene->addChild( camera );

  float rotationSpeed = 0.02f;

  auto node = generateGeom( mb::Color::WHITE, "earth/earth_diffuse.jpg" );
  scene->addChild( node );
  node->addComponent( new RotationComponent( rotationSpeed ) );

  auto node2 = generateGeom( mb::Color::WHITE, "earth/earth_clouds.png" );
  node2->getComponent<mb::MaterialComponent>( )->
    first( )->state( ).blending( ).setEnabled( true );
  node2->local( ).setScale( 1.005f );
  node2->addComponent( new RotationComponent( 1.25f * rotationSpeed ) );
  scene->addChild( node2 );


  auto node3 = generateGeom( mb::Color::WHITE, "earth/space.png" );
  node3->local( ).setScale( 15.0f );
  scene->addChild( node3 );

  return scene;
}

int main( )
{
  mb::FileSystem::getInstance( )->setBaseDirectory( MB_EXAMPLES_RESOURCES_ROUTE );

  mb::Window* window = new mb::GLFWWindow2( mb::WindowParams( 500, 500 ) );
  window->init( );
  window->setTitle( "Earth" );

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
