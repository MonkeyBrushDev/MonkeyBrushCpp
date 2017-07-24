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

#include <chrono>

#define EARTH_NM

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
    _time += _speed * clock.getDeltaTime( );
  }
protected:
  float _speed;
  float _time;
};

mb::Group* createPlanet( float radius, const std::string& diffuse, float equatorialRotationSpeed,
  float orbitSize, float sideralRotationSpeed, const mb::Color& color )
{
  auto geometry = new mb::Geometry( );
  geometry->local( ).setScale( radius );
  geometry->layer( ).set( 0 );
  geometry->addPrimitive( new mb::SpherePrimitive( 1.0f, 15, 15 ) );


  auto planetRotationPivot = new mb::Group( "" );
  planetRotationPivot->addComponent( new RotationComponent( equatorialRotationSpeed ) );
  planetRotationPivot->addChild( geometry );

#ifdef EARTH_NM
  mb::StandardMaterial* customMaterial = new mb::StandardMaterial( );
  customMaterial->setColorMap( mb::Texture2D::loadFromImage( diffuse ) );
  customMaterial->setNormalMap( mb::Texture2D::loadFromImage( "earth/earth_normal.jpg" ) );
  customMaterial->setNormalScale( 2.5f );
  customMaterial->setColor( color );
#else
  mb::ColorMaterial* customMaterial = new mb::ColorMaterial( );
  customMaterial->setColorMap( mb::Texture2D::loadFromImage( diffuse ) );
  customMaterial->setNormalMap( mb::Texture2D::loadFromImage( "metal-floor-normal.jpg" ) );
  customMaterial->setColor( color );
#endif

  mb::MaterialComponent* mc = geometry->getComponent<mb::MaterialComponent>( );
  mc->addMaterial( mb::MaterialPtr( customMaterial ) );

  auto planet = new mb::Group( "name" );
  planet->addChild( planetRotationPivot );
  planet->local( ).setPosition( orbitSize, 0.0f, 0.0f );

  auto planetPivot = new mb::Group( "" );
  planetPivot->addComponent( new RotationComponent( sideralRotationSpeed ) );
  planetPivot->addChild( planet );

  return planetPivot;
}

mb::Group* createScene( void )
{
  auto scene = new mb::Group( "scene" );

  auto camera = new mb::Camera( 45.0f, 500 / 500, 0.01f, 1000.0f );
  camera->local( ).translate( 0.0f, 0.0f, 8.0f );

  camera->addComponent( new mb::FreeCameraComponent( ) );
  scene->addChild( camera );

  auto cubes = new mb::Group( "Cubes" );
  mb::Group* g1 = new mb::Group( "MyGroup1" );
  mb::Group* g2 = new mb::Group( "MyGroup2" );

  mb::Texture2D* chesterDiffuse = mb::Texture2D::loadFromImage( "metal-floor.jpg" );
  mb::Texture2D* chesterDNormal = mb::Texture2D::loadFromImage( "metal-floor-normal.jpg" );

#if 0
  mb::StandardMaterial* customMaterial = new mb::StandardMaterial( );
  customMaterial->setColorMap( chesterDiffuse );
  customMaterial->setNormalMap( chesterDNormal );
  customMaterial->setColor( mb::Color::GREEN );

  mb::StandardMaterial* customMaterial2 = new mb::StandardMaterial( );
  customMaterial2->setColorMap( chesterDiffuse );
  customMaterial2->setNormalMap( chesterDNormal );
  customMaterial2->setColor( mb::Color::GOLD );

#else
  mb::ColorMaterial* customMaterial = new mb::ColorMaterial( );
  customMaterial->setColorMap( chesterDiffuse );
  customMaterial->setNormalMap( chesterDNormal );
  customMaterial->setColor( mb::Color::GREEN );

  mb::ColorMaterial* customMaterial2 = new mb::ColorMaterial( );
  customMaterial2->setColorMap( chesterDiffuse );
  customMaterial2->setNormalMap( chesterDNormal );
  customMaterial2->setColor( mb::Color::GOLD );
#endif


  std::vector< mb::Vector3 > cubePositions = {
    mb::Vector3( 2.0f, 3.0f, -15.0f ),
    mb::Vector3( 0.0f, -3.0f, 0.0f ),
    mb::Vector3( -1.5f, -2.2f, -2.5f ),
    mb::Vector3( -3.8f, -2.0f, -12.3f ),
    mb::Vector3( 2.4f, -0.4f, -3.5f ),
    mb::Vector3( -1.7f, 3.0f, -7.5f ),
    mb::Vector3( 1.3f, -2.0f, -2.5f ),
    mb::Vector3( 1.5f, 2.0f, -2.5f ),
    mb::Vector3( 1.5f, 0.2f, -1.5f ),
    mb::Vector3( -1.3f, 1.0f, -1.5f )
  };

  size_t numCubes = cubePositions.size( );
  size_t middleCubes = numCubes / 2;
  for ( unsigned int i = 0; i < middleCubes; ++i )
  {
    auto geom = new mb::Geometry( std::string( "CubeGeom" ) + std::to_string( i + 1 ) );
    geom->local( ).position( ) = cubePositions[ i ];
    geom->local( ).setScale( mb::Vector3( 0.5f ) );
    geom->addPrimitive( new mb::CubePrimitive( 2.0f ) );

    mb::MaterialComponent* mc = geom->getComponent<mb::MaterialComponent>( );
    mc->addMaterial( mb::MaterialPtr( customMaterial ) );

    geom->addComponent( new RotationComponent( 0.1f ) );
    //geom->addComponent( new mb::RotateComponent( mb::Vector3( -1.0f, -1.0f, 0.0f ), 0.1f ) );
    geom->layer( ).set( i );
    g1->addChild( geom );
  }
  cubes->addChild( g1 );
  for ( unsigned int i = middleCubes; i < numCubes; ++i )
  {
    auto geom = new mb::Geometry( std::string( "CubeGeom" ) + std::to_string( i + 1 ) );
    geom->local( ).setPosition( cubePositions[ i ] );
    geom->local( ).setScale( mb::Vector3( 0.5f ) );
    geom->addPrimitive( new mb::SpherePrimitive( 1.0f, 15, 15 ) );

    mb::MaterialComponent* mc = geom->getComponent<mb::MaterialComponent>( );
    mc->addMaterial( mb::MaterialPtr( customMaterial2 ) );

    geom->addComponent( new RotationComponent( 0.1f ) );
    //geom->addComponent( new mb::RotateComponent( mb::Vector3( -1.0f, -1.0f, 0.0f ) * -1.0f, 0.1f ) );
    geom->layer( ).set( i );
    g2->addChild( geom );
  }
  cubes->addChild( g2 );

  scene->addChild( cubes );

  auto earth = createPlanet( 0.5f, "earth.png", 0.05f, 0.5f, 0.1f, mb::Color::WHITE );
  auto moon = createPlanet( 0.15f, "moon.png", 0.025f, 1.15f, 0.035f, mb::Color::BROWN );

  scene->addChild( earth );
  earth->nodeAt<mb::Group>( 0 )->addChild( moon );

  return scene;
}

int main( )
{
  mb::FileSystem::getInstance( )->setBaseDirectory( MB_EXAMPLES_RESOURCES_ROUTE );

  mb::Window* window = new mb::GLFWWindow2( mb::WindowParams( 500, 500 ) );
  window->init( );
  window->setTitle( "Normal Mapping (WIP)" );

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
