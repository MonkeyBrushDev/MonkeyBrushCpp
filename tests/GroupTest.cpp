/**
 * Copyright (c) 2017, Monkey Brush
 * All rights reserved.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

#include "mbTests.h"
#include <mb/mb.h>

using namespace mb;

BOOST_AUTO_TEST_CASE( test_group_construction )
{
  const char* name = "firstGroup";
  auto group = new mb::Group( name );
  BOOST_CHECK_EQUAL( group->name( ), name );
  BOOST_CHECK_FALSE( group->hasNodes( ) );
}

BOOST_AUTO_TEST_CASE( test_group_destruction )
{
  auto child1 = new mb::Group( "child1" );
  auto child2 = new mb::Group( "child2" );
  auto parent = new mb::Group( "parent" );

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
  auto child1 = new mb::Group("child1");
  auto child2 = new mb::Group("child2");
  auto parent = new mb::Group("parent");
  BOOST_CHECK_EQUAL(parent->getNumChildren(), 0);
  BOOST_CHECK_FALSE( parent->hasNodes( ) );

  parent->addChild(child1);
  BOOST_CHECK_EQUAL(parent->getNumChildren( ), 1);
  BOOST_CHECK_TRUE( parent->hasNodes( ) );

  parent->addChild(child2);
  BOOST_CHECK_EQUAL(parent->getNumChildren( ), 2);
  BOOST_CHECK_TRUE( parent->hasNodes( ) );

  parent->removeChild(child2);
  BOOST_CHECK_EQUAL(parent->getNumChildren( ), 1);
  BOOST_CHECK_TRUE( parent->hasNodes( ) );

  parent->removeChild(child1);
  BOOST_CHECK_EQUAL(parent->getNumChildren( ), 0);
  BOOST_CHECK_FALSE( parent->hasNodes( ) );
}

BOOST_AUTO_TEST_CASE( test_group_hierarchy )
{
  /*    node0
        /   \
      node1 node2
          / \
        node3 node4
  */

  const char* rootName = "root";

  std::vector< std::string > groupNodes;
  for ( unsigned int i = 1; i < 5; ++i )
  {
    groupNodes.push_back( std::string("node") + std::to_string(i) );
  }
  unsigned int i = 0;

  auto node0 = new mb::Group( rootName );
  auto node1 = new mb::Group( groupNodes[i++] );
  auto node2 = new mb::Group( groupNodes[i++] );
  auto node3 = new mb::Group( groupNodes[i++] );
  auto node4 = new mb::Group( groupNodes[i++] );

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

  for( unsigned int j = 0, l = node0->getNumChildren( ); j < l; ++j )
  {
    BOOST_CHECK_EQUAL( node0->nodeAt( j )->name( ), groupNodes[ j ] );
  }
}

class ParentVisitorName : public Visitor
{
public:
  virtual void visitNode( Node* n ) override
  {
    if ( n->hasParent( ) )
    {
      n->name( n->parent( )->name( ) + "_" + n->name( ) );
    }
  }
  virtual void visitGroup( Group * g ) override
  {
    visitNode( g );
    Visitor::visitGroup( g );
  }
};

BOOST_AUTO_TEST_CASE( test_group_full )
{
  auto group = new Group( "First group" );
  BOOST_CHECK_EQUAL( group->name( ), "First group" );
  BOOST_CHECK_FALSE( group->hasNodes( ) );

  auto lChild = new Group( "LChild" );
  BOOST_CHECK_FALSE( lChild->hasParent( ) );
  auto rChild = new Group( "RChild" );
  BOOST_CHECK_FALSE( rChild->hasParent( ) );

  group->addChild( lChild );
  BOOST_CHECK_EQUAL( group->getNumChildren( ), 1 );
  BOOST_CHECK_FALSE( group->hasParent( ) );
  BOOST_CHECK_TRUE( lChild->hasParent( ) );
  group->addChild( rChild );
  BOOST_CHECK_EQUAL( group->getNumChildren( ), 2 );
  BOOST_CHECK_TRUE( lChild->hasParent( ) );

  unsigned int count = 0;
  group->forEachNode( [ &] ( Node* )
  {
    ++count;
  } );
  BOOST_CHECK_EQUAL( count, 2 );

  // Reattach
  BOOST_CHECK_EQUAL( group->getNumChildren( ), 2 );
  BOOST_CHECK_THROW(
    group->addChild( lChild ),
    mb::RuntimeException
  );
  ;
  BOOST_CHECK_EQUAL( group->getNumChildren( ), 2 );

  // Detach
  group->removeChild( lChild );
  BOOST_CHECK_EQUAL( group->getNumChildren( ), 1 );
  group->addChild( lChild );
  BOOST_CHECK_EQUAL( group->getNumChildren( ), 2 );

  // Detach all mb
  BOOST_CHECK_TRUE( group->hasNodes( ) );
  group->removeChildren( );
  BOOST_CHECK_FALSE( group->hasNodes( ) );


  /*    node0
        /   \
      node1 node2
            / \
        node3 node4
  */

  {
    auto node0 = new Group( "node0" );
    auto node2 = new Group( "node2" );
    auto node1 = new Node( "node1" );
    auto node3 = new Node( "node3" );
    auto node4 = new Node( "node4" );

    node0->addChild( node1 );
    node0->addChild( node2 );
    node2->addChild( node3 );
    node2->addChild( node4 );

    node0->perform( ParentVisitorName( ) );

    BOOST_CHECK_EQUAL( node0->name( ), "node0" );
    BOOST_CHECK_EQUAL( node1->name( ), "node0_node1" );
    BOOST_CHECK_EQUAL( node2->name( ), "node0_node2" );
    BOOST_CHECK_EQUAL( node3->name( ), "node0_node2_node3" );
    BOOST_CHECK_EQUAL( node4->name( ), "node0_node2_node4" );
  }


  auto root = new Group( "Root" );
  auto node0 = new Group( "node0" );
  root->addChild( node0 );
  FetchLights fl;
  root->perform( fl );
  BOOST_CHECK_EQUAL( fl.lights( ).size( ), 0 );
  node0->addChild( new Light( ) );
  root->perform( fl );
  BOOST_CHECK_EQUAL( fl.lights( ).size( ), 1 );
  root->addChild( new Light( ) );
  root->perform( fl );
  BOOST_CHECK_EQUAL( fl.lights( ).size( ), 2 );
}
