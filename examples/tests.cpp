#include <iostream>
#include <mb/mb.h>
#include <string>
#include <assert.h>
#include <routes.h>
using namespace mb;

int main( )
{
  mb::FileSystem::getInstance( )->setBaseDirectory( MB_EXAMPLES_RESOURCES_ROUTE );

  //mb::ObjLoader::loadObj( "objects/wolf.obj_" );
  //mb::ObjLoader::readMaterialFile( "materials/customMaterial.mtl_" );

  auto group = new Group( "First group" );

  auto lChild = new Group( "LChild" );
  group->addChild( lChild );
  group->addChild( lChild );

  system( "PAUSE" );
  return 0;
}
