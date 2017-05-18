#include "mbTests.h"
#include <mb/mb.h>

using namespace mb;

BOOST_AUTO_TEST_CASE( test_node_construction )
{
	const char* name = "myNode";
	auto node = Node::create( name );
	//BOOST_CHECK_EQUAL( node->name( ), name );
	BOOST_CHECK_FALSE( node->hasParent( ) );
	//BOOST_CHECK_IS_NULL( node->parent( ) );
}

BOOST_AUTO_TEST_CASE( test_node_add_child )
{
	const char* rootName = "rootNode";
	const char* childName = "childName";
	auto root = Node::create( rootName );
	auto child = Node::create( childName );
	root->addChild( child );
	BOOST_CHECK_EQUAL( child->parent( ), root );
  BOOST_CHECK_TRUE( child->hasParent( ) );
	BOOST_CHECK_FALSE( root->hasParent( ) );
}
/*
BOOST_AUTO_TEST_CASE( test_node_attach_component )
{
	auto node = Node::create( "fooNode" );
	auto comp = std::make_shared< mb::MoveComponent>( );
	node->addComponent( comp );
	BOOST_CHECK_EQUAL( comp->getNode( ), node );
	BOOST_CHECK_EQUAL( node->getComponent<mb::MoveComponent>( ), comp );
}

BOOST_AUTO_TEST_CASE( test_invalid_component )
{
	auto node = Node::create( "fooNode" );
	BOOST_CHECK_EQUAL( node->getComponent<mb::MoveComponent>( ), nullptr );
}

BOOST_AUTO_TEST_CASE( test_component_by_name )
{
	auto node = Node::create( "fooNode" );
	BOOST_CHECK_EQUAL( node->getComponentByName( "mb::MoveComponent" ), nullptr);
	auto comp = std::make_shared< mb::MoveComponent>( );
	BOOST_CHECK_EQUAL( node->getComponentByName( "mb::MoveComponent" ), comp);
}
*/
BOOST_AUTO_TEST_CASE( test_detach_all_components )
{
	auto node = Node::create( "fooNode" );
	auto comp = std::make_shared< mb::MoveComponent>( );
	auto comp2 = std::make_shared< mb::RotateComponent>( mb::Vect3( 1.0f, 0.0f, 1.0f ) );
	BOOST_CHECK_EQUAL( node->getNumComponents( ), 0 );
	node->addComponent( comp );
	BOOST_CHECK_EQUAL( node->getNumComponents( ), 1 );
	node->addComponent( comp2 );
	BOOST_CHECK_EQUAL( node->getNumComponents( ), 2 );
	node->removeComponents( );
	//BOOST_CHECK_IS_NULL( node->getComponent<mb::MoveComponent>( ) );
	BOOST_CHECK_EQUAL( node->getNumComponents( ), 0 );
}

BOOST_AUTO_TEST_CASE( test_node_compare_parent )
{
	auto root = Node::create( "rootNode" );
	auto nodeLeft = Node::create( "leftNode" );
	auto nodeRight = Node::create( "RightNode" );
	root->addChild( nodeLeft );
	root->addChild( nodeRight );
	BOOST_CHECK_EQUAL( nodeLeft->parent( ), nodeRight->parent( ) );
	BOOST_CHECK_TRUE( nodeLeft->hasParent( ) );
	BOOST_CHECK_TRUE( nodeRight->hasParent( ) );
}
