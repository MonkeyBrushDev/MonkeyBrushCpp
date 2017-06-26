#include "mbTests.h"
#include <mb/mb.h>

using namespace mb;

BOOST_AUTO_TEST_CASE( test_switch_construction )
{
  auto switchNode = new Switch( "" );
  BOOST_CHECK_EQUAL( switchNode->getNumChildren( ), 0 );
  BOOST_CHECK_FALSE( switchNode->hasParent( ) );
  auto node1 = new Node( "node1" );
  switchNode->addChild( node1 );
  auto node2 = new Node( "node2" );
  switchNode->addChild( node2 );

  BOOST_CHECK_EQUAL( switchNode->getNumChildren( ), 2 );
  BOOST_CHECK_EQUAL( switchNode->nodeAt<mb::Node>( 0 ), node1 );
  BOOST_CHECK_EQUAL( switchNode->nodeAt<mb::Node>( 1 ), node2 );

  // Default currentNodeIdx is 0
  BOOST_CHECK_EQUAL( switchNode->nodeAt<mb::Node>(
    switchNode->getActiveChild( ) ), node1 );

  switchNode->setActiveChild( 1 );

  BOOST_CHECK_EQUAL( switchNode->nodeAt<mb::Node>(
    switchNode->getActiveChild( ) ), node2 );
}

BOOST_AUTO_TEST_CASE( test_switch_foreachChildren )
{
  auto switchNode = new Switch( "" );
  BOOST_CHECK_EQUAL( switchNode->getNumChildren( ), 0 );
  BOOST_CHECK_FALSE( switchNode->hasParent( ) );
  auto node1 = new Node( "node1" );
  switchNode->addChild( node1 );
  auto node2 = new Node( "node2" );
  switchNode->addChild( node2 );

  switchNode->setActiveChild( 1 );

  unsigned int numNodes = 0;
  switchNode->forEachNode( [ & ] ( mb::Node* node )
  {
    BOOST_CHECK_EQUAL( node2, node );
    ++numNodes;
  } );
  BOOST_CHECK_EQUAL( numNodes, 1 );
}
