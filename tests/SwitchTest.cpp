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
