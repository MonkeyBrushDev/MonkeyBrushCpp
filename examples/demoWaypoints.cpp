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

class WaypointMoveComponent : public mb::Component
{
  IMPLEMENT_COMPONENT( WaypointMoveComponent )
public:
  WaypointMoveComponent( const std::vector< mb::Vector3 >& positions )
    : mb::Component( )
    , wayPoints( positions )
  {
  }
  virtual void start( void ) override
  {
    if ( !wayPoints.empty( ) )
    {
      currentWayPoint = &wayPoints.front( );
    }
  }
  virtual void update( const mb::Clock& c ) override
  {
    if ( currentWayPoint != nullptr )
    {
      moveTowardsWaypoint( c.getDeltaTime() );
    }
  }
private:
  void moveTowardsWaypoint( const float& dt )
  {
    mb::Vector3 currentPosition = node( )->local( ).getPosition( );
    mb::Vector3 targetPosition = *currentWayPoint;

    if ( ( currentPosition - targetPosition ).length( ) > 0.1f )
    {
      mb::Vector3 directionOfTravel = targetPosition - currentPosition;
      directionOfTravel.normalize( );

      node( )->local( ).translate( mb::Vector3(
        directionOfTravel.x( ) * speed * dt,
        directionOfTravel.y( ) * speed * dt,
        directionOfTravel.z( ) * speed * dt
        ) );
    }
    else
    {
      if ( speedStorage != 0.0f )
      {
        speed = speedStorage;
        speedStorage = 0.0f;
      }
      nextWayPoint( );
    }
  }
  void nextWayPoint( void )
  {
    if ( isCircular )
    {
      if ( !inReverse )
      {
        currentIndex = ( currentIndex + 1 >= wayPoints.size( ) ) ? 0 : currentIndex + 1;
      }
      else
      {
        currentIndex = ( currentIndex == 0 ) ? wayPoints.size( ) - 1 : currentIndex - 1;
      }
    }
    else
    {
      // If at the start or the end then reverse
      if ( ( !inReverse && currentIndex + 1 >= wayPoints.size( ) ) || ( inReverse && currentIndex == 0 ) )
      {
        inReverse = !inReverse;
      }
      currentIndex = ( !inReverse ) ? currentIndex + 1 : currentIndex - 1;
    }
    currentWayPoint = &wayPoints[ currentIndex ];
  }
protected:
  std::vector< mb::Vector3 > wayPoints;
  mb::Vector3* currentWayPoint;

  float speed = 3.0f;
  bool isCircular = true;
  // Always true at the beginning because the moving object will always move towards the first waypoint
  bool inReverse = true;

  unsigned int currentIndex = 0;
  float speedStorage = 0.0f;
};

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

  return geom;
}
mb::Geometry* generateGeom2( const mb::Color& c )
{
  auto geom = new mb::Geometry( );
  geom->addPrimitive( new mb::SpherePrimitive( 1.0f, 25, 25 ) );

  mb::BasicMaterial* customMaterial = new mb::BasicMaterial( );
  customMaterial->setColor( c );

  mb::MaterialComponent* mc = geom->getComponent<mb::MaterialComponent>( );
  mc->addMaterial( mb::MaterialPtr( customMaterial ) );

  return geom;
}

mb::Group* addCube( void )
{
  auto cubeSize = 1.0f;
  auto cubeGeometry = generateGeom( mb::Color::randomColor( ) );
  cubeGeometry->local( ).setScale( cubeSize );
  auto cube = new mb::Group( "cube" );
  cube->addChild( cubeGeometry );

  mb::Vector3 pos = cube->local( ).getPosition( );
  pos.x( ) = 5.41f;
  pos.y( ) = 0.0f;
  pos.z( ) = -8.41f;

  cube->local( ).setPosition( pos );

  return cube;
}

mb::Group* addSphere( const mb::Vector3& pos )
{
  auto sphereSize = 0.25f;
  auto sphereGeometry = generateGeom2( mb::Color::randomColor( ) );
  sphereGeometry->local( ).setPosition( pos );
  sphereGeometry->local( ).setScale( sphereSize );
  auto sphere = new mb::Group( "cube" );
  sphere->addChild( sphereGeometry );

  return sphere;
}

mb::Group* createScene( void )
{
  auto scene = new mb::Group( "scene" );

  auto camera = new mb::Camera( 70.0f, 500 / 500, 0.03f, 1000.0f );
  camera->local( ).translate( 4.32f, 1.0f, -13.82f );

  camera->addComponent( new mb::FreeCameraComponent( ) );
  scene->addChild( camera );

  scene->addChild( addCube( ) );

  scene->addChild( addSphere( mb::Vector3( 6.82f, -1.38f, -2.51f ) ) );
  scene->addChild( addSphere( mb::Vector3( 1.06f, 2.59f, -3.46f ) ) );
  scene->addChild( addSphere( mb::Vector3( 1.48f, -0.81f, -7.32f ) ) );
  scene->addChild( addSphere( mb::Vector3( 7.23f, -2.46f, -6.26f ) ) );
  
  return scene;
}

int main( )
{
  mb::FileSystem::getInstance( )->setBaseDirectory( MB_EXAMPLES_RESOURCES_ROUTE );

  mb::Window* window = new mb::GLFWWindow2( mb::WindowParams( 500, 500 ) );
  window->init( );
  window->setTitle( "Multicubes" );

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
