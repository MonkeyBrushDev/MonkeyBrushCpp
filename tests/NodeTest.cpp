#include "mbTests.h"
#include <mb/mb.h>

using namespace mb;

BOOST_AUTO_TEST_CASE( test_node_construction )
{
  const char* name = "myNode";
  auto node = new Node( name );
  BOOST_CHECK_EQUAL( node->name( ), name );
  BOOST_CHECK_FALSE( node->hasParent( ) );
  // TODO BOOST_CHECK_IS_NULL( node->parent( ) );
}

BOOST_AUTO_TEST_CASE( test_node_compare_parent )
{
  auto root = new mb::Group( "rootNode" );
  auto nodeLeft = new mb::Node( "leftNode" );
  auto nodeRight = new mb::Node( "RightNode" );
  root->addChild( nodeLeft );
  root->addChild( nodeRight );
  BOOST_CHECK_EQUAL( nodeLeft->parent( ), nodeRight->parent( ) );
  BOOST_CHECK_TRUE( nodeLeft->hasParent( ) );
  BOOST_CHECK_TRUE( nodeRight->hasParent( ) );
}
