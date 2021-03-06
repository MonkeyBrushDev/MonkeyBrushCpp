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

BOOST_AUTO_TEST_CASE( test_node_construction )
{
  const char* name = "myNode";
  auto node = new Node( name );
  BOOST_CHECK_EQUAL( node->name( ), name );
  BOOST_CHECK_FALSE( node->hasParent( ) );
  BOOST_CHECK_IS_NULL( node->parent( ) );
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
