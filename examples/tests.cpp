#include <iostream>
#include <mb/mb.h>
#include <string>
#include <assert.h>
using namespace mb;

int main( )
{
  auto switchNode = new Switch( "" );
  std::cout << ( switchNode->getNumChildren( ) == 0 ) << std::endl;
  std::cout << ( !switchNode->hasParent( ) ) << std::endl;
  auto node1 = new Node( "node1" );
  switchNode->addChild( node1 );
  auto node2 = new Node( "node2" );
  switchNode->addChild( node2 );

  std::cout << ( switchNode->getNumChildren( ) == 2 ) << std::endl;
  std::cout << ( switchNode->nodeAt<mb::Node>( 0 ) == node1 ) << std::endl;
  std::cout << ( switchNode->nodeAt<mb::Node>( 1 ) == node2 ) << std::endl;

  std::cout << ( switchNode->nodeAt<mb::Node>(
    switchNode->getCurrentNodeIndex( ) ) == node1 ) << std::endl;

  switchNode->setCurrentNodeIndex( 1 );

  std::cout << ( switchNode->nodeAt<mb::Node>(
    switchNode->getCurrentNodeIndex( ) ) == node2 ) << std::endl;

  unsigned int numNodes = 0;
  switchNode->forEachNode( [ & ] ( mb::Node* node )
  {
    std::cout << ( node2 == node ) << std::endl;
    ++numNodes;
  } );
  std::cout << ( numNodes == 1 ) << std::endl;

  system( "PAUSE" );
  return 0;
}
