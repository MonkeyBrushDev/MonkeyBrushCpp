#include <iostream>

#include <mb/mb.h>
using namespace mb;

int main( )
{
  auto scene = new Scene( "scene" );

  auto geom = new Geometry( "nodeGeom" );
  geom->addPrimitive( new Primitive( "FirstPrimitive" ) );
  scene->addChild( geom );
  geom->layer( ).set( 2 );

  auto camera = new Camera( );
  camera->name( "PPCamera" );
  camera->renderPass( new PostRenderingPass( new StandardRenderingPass( ) ) );
  camera->renderPass( )->imageEffects( ).push_back( new SepiaToneEffect( ) );
  camera->renderPass( )->imageEffects( ).push_back( new GreyToneEffect( ) );
  scene->addChild( camera );

  camera->layer( ).enable( 1 );
  camera->layer( ).enable( 2 );
  camera->layer( ).enable( 3 );

  mb::DumpVisitor dv;
  dv.traverse( scene );

  App app;
  app.setSceneNode( scene );
  app.run( );

  /*std::cout << std::endl << std::endl << std::endl;

  geom->layer( ).set( 4 );
  e.run( );*/
  delete scene;
  system( "PAUSE" );
  return 0;
}
