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

mb::Geometry* generateGeom( const mb::Color& c )
{
  auto geom = new mb::Geometry( );
  geom->addPrimitive( new mb::CubePrimitive( 1.0f ) );

  mb::BasicMaterial* customMaterial = new mb::BasicMaterial( );
  customMaterial->setColor( c );

  mb::MaterialComponent* mc = geom->getComponent<mb::MaterialComponent>( );
  mc->addMaterial( mb::MaterialPtr( customMaterial ) );

  geom->addComponent( new mb::RotateComponent( mb::Vector3::ONE, 0.25f ) );

  return geom;
}

#include <random>

// Returns random values uniformly distributed in the range [a, b]
float _random( )
{
  return static_cast <float> ( rand( ) ) / static_cast <float> ( RAND_MAX );
}

mb::Group* addCube( void )
{
  auto cubeSize = std::ceil( _random( ) * 3 );
  auto cubeGeometry = generateGeom( mb::Color::randomColor( ) );
  cubeGeometry->local( ).setScale( cubeSize );
  auto cube = new mb::Group( "cube" );
  cube->addChild( cubeGeometry );

  mb::Vector3 pos = cube->local( ).getPosition( );
  pos.x( ) = -30.0f + std::round( _random( ) * 100.0f );
  pos.y( ) = std::round( _random( ) * 5 );
  pos.z( ) = -20.0f + std::round( _random( ) * 100.0f );

  cube->local( ).setPosition( pos );
  
  return cube;
}

mb::Group* createScene( void )
{
  auto scene = new mb::Group( "scene" );

  auto camera = new mb::Camera( 75.0f, 500 / 500, 0.03f, 1000.0f );
  camera->local( ).translate( 0.0f, 10.0f, 50.0f );

  camera->addComponent( new mb::FreeCameraComponent( ) );
  scene->addChild( camera );

  for ( int i = 0; i < 185; ++i )
  {
    scene->addChild( addCube( ) );
  }

  return scene;
}

int main( )
{
  mb::FileSystem::getInstance( )->setBaseDirectory( MB_EXAMPLES_RESOURCES_ROUTE );

  mb::Window* window = new mb::GLFWWindow2( mb::WindowParams( 500, 500 ) );
  window->init( );
  window->setTitle( "Multicubes" );

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