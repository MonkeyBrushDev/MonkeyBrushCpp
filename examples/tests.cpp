#include <iostream>
#include <mb/mb.h>
#include <string>
#include <assert.h>
#include <routes.h>
using namespace mb;

int main( )
{
  mb::FileSystem::getInstance( )->setBaseDirectory( MB_EXAMPLES_RESOURCES_ROUTE );
  
  mb::ObjLoader::loadObj( "objects/cube.obj_" );
  mb::ObjLoader::readMaterialFile( "materials/customMaterial.mtl_" );

  system( "PAUSE" );
  return 0;
}
