#include "mbTests.h"
#include <mb/mb.h>

using namespace mb;

BOOST_AUTO_TEST_CASE( test_group_construction )
{
	const char* name = "firstGroup";
	auto group = Group::create( name );
	BOOST_CHECK_EQUAL( group->name( ), name );
	BOOST_CHECK_FALSE( group->hasNodes( ) );
}

BOOST_AUTO_TEST_CASE( test_group_destruction )
{
	auto child1 = Group::create( "child1" );
	auto child2 = Group::create( "child2" );
	auto parent = Group::create( "parent" );

	BOOST_CHECK_FALSE( child1->hasParent( ) );
	BOOST_CHECK_FALSE( child2->hasParent( ) );

	parent->addChild( child1 );
	BOOST_CHECK_TRUE( child1->hasParent( ) );
	BOOST_CHECK_EQUAL( child1->parent( ), parent );

	parent->addChild( child2 );
	BOOST_CHECK_TRUE( child2->hasParent( ) );
	BOOST_CHECK_EQUAL( child2->parent( ), parent );
}

BOOST_AUTO_TEST_CASE( test_group_detach )
{
	auto child1 = Group::create("child1");
	auto child2 = Group::create("child2");
	auto parent = Group::create("parent");
	BOOST_CHECK_EQUAL(parent->getNumChildren(), 0);

	parent->addChild(child1);
	BOOST_CHECK_EQUAL(parent->getNumChildren(), 1);

	parent->addChild(child2);
	BOOST_CHECK_EQUAL(parent->getNumChildren(), 2);

	parent->removeChild(child2);
	BOOST_CHECK_EQUAL(parent->getNumChildren(), 1);

	parent->removeChild(child1);
	BOOST_CHECK_EQUAL(parent->getNumChildren(), 0);
}

BOOST_AUTO_TEST_CASE( test_group_hierarchy )
{
	//		node0
	//		/   \
	//	node1	node2
	//			/	\
	//		node3	node4

  const char* rootName = "root";

	auto node0 = Group::create( rootName );
	auto node1 = Group::create( "node1" );
	auto node2 = Group::create( "node2" );
	auto node3 = Group::create( "node3" );
	auto node4 = Group::create( "node4" );

	node0->addChild( node1 );
	node0->addChild( node2 );
	node2->addChild( node3 );
	node2->addChild( node4 );

	BOOST_CHECK_TRUE( node0->hasNodes( ) );
	BOOST_CHECK_EQUAL( node1->parent( ), node0 );
	BOOST_CHECK_EQUAL( node2->parent( ), node0 );

	BOOST_CHECK_TRUE( node2->hasNodes( ) );
	BOOST_CHECK_EQUAL( node3->parent( ), node2 );
	BOOST_CHECK_EQUAL( node4->parent( ), node2 );

  BOOST_CHECK_EQUAL( node4->parent( )->parent( )->name( ), rootName );
}
