#include <iostream>

#include <mb/mb.h>

using namespace mb;

#include <vector>

class CarController : public mb::Component
{
  IMPLEMENT_COMPONENT( CarController )
public:
  virtual void start( )
  {
    FindNodes findLightsVisitor( [ &] ( Node*n )
    {
      if ( n->tag == "Light" )
      {
        return true;
      }
      return false;
    } );
    findLightsVisitor.traverse( node( ) );
    _lights = findLightsVisitor.matches( );
    FindNodes findWheelVisitor( [ &] ( Node*n )
    {
      if ( n->tag == "Wheel" )
      {
        return true;
      }
      return false;
    } );
    findWheelVisitor.traverse( node( ) );
    _wheels = findWheelVisitor.matches( );
  }
  std::vector<Node*> _lights;
  std::vector<Node*> _wheels;
};

int main( )
{
  auto scene = new Scene( "scene" );

  auto car = new Group( "car" );
  scene->addChild( car );

  auto front = new Group( "front" );
  for ( unsigned int i = 0; i < 2; ++i )
  {
    auto light = new Light( );
    light->name( std::string("Light") + std::to_string( i + 1 ) );
    light->tag = "Light";
    front->addChild( light );
  }
  car->addChild( front );

  auto wheels = new Group( "wheels" );
  for ( unsigned int i = 0; i < 4; ++i )
  {
    auto wheel = new Geometry(
      std::string("Wheel") +
      std::to_string( i + 1 )
    );
    wheel->tag = "Wheel";
    wheels->addChild( wheel );
  }
  car->addChild( wheels );

  car->addComponent( new CarController( ) );


  auto cam = new Camera( );
  Camera::mainCamera( cam );
  scene->addChild( cam );


  mb::DumpVisitor dv;
  dv.traverse( scene );

  App app;
  app.setSceneNode( scene );
  app.run( );
  delete scene;
  system( "PAUSE" );
  return 0;
}
