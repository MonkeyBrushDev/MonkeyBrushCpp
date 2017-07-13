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

BOOST_AUTO_TEST_CASE( test_transform_construction )
{
  mb::Transform transform;
  transform.setPosition( mb::Vector3::FORWARD );
  BOOST_CHECK_EQUAL( transform.getPosition( ), mb::Vector3::FORWARD );
}

/*BOOST_AUTO_TEST_CASE( test_from_matrix )
{
  mb::Transform transform( mb::Matrix4( {
    1.0f, 0.0f, 0.0f, 0.0,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    2.0f, 6.0f, 8.0f, 1.0f
  } ) );

  BOOST_CHECK_EQUAL( transform.getPosition( ), mb::Vector3( 2.0f, 6.0f, 8.0f ) );
  BOOST_CHECK_EQUAL( transform.getRotation( ), mb::Quaternion( ) );
  BOOST_CHECK_EQUAL( transform.getScale( ), mb::Vector3::ONE );
}*/
