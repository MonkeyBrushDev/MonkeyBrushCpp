#include <iostream>

#include <mb/mb.h>
using namespace mb;

int main( )
{
  auto scene = new Scene( "scene" );

  auto node0 = new Group( "node0" );
  auto node2 = new Group( "node2" );
  auto node1 = new Node( "node1" );
  auto node3 = new Node( "node3" );
  auto node4 = new Node( "node4" );

  node0->addChild( node1 );
  node0->addChild( node2 );
  node2->addChild( node3 );
  node2->addChild( node4 );

  scene->addChild( node0 );

  auto camera = new Camera( );
  scene->addChild( camera );

  mb::DumpVisitor dv;
  dv.traverse( scene );

  App app;
  app.setSceneNode( scene );
  app.run( );
  delete scene;
  system( "PAUSE" );
  return 0;
}
