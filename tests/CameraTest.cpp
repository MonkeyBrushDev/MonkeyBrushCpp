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

BOOST_AUTO_TEST_CASE( test_camera_construction )
{
  float near = 0.01f;
  float far = 1000.0f;
  unsigned int width = 500;
  unsigned int height = 500;
  float aspectRatio = width / height;
  float fov = 70.0f;
  mb::Camera camera( fov, aspectRatio, near, far );

  BOOST_CHECK_EQUAL( camera.name( ), std::string( "Camera" ) );
}

BOOST_AUTO_TEST_CASE( test_camera_view )
{
  mb::Camera camera;
  camera.local( ).setPosition( Vector3( 1.0f, 2.0f, 3.0f ) );
  camera.perform( mb::UpdateWorldState( ) );

  mb::Matrix4 viewMatrix = camera.getView( );

  BOOST_CHECK_EQUAL( viewMatrix[ 12 ], -1.0f );
  BOOST_CHECK_EQUAL( viewMatrix[ 13 ], -2.0f );
  BOOST_CHECK_EQUAL( viewMatrix[ 14 ], -3.0f );
}

BOOST_AUTO_TEST_CASE( test_camera_projection )
{
  float near = 0.01f;
  float far = 1000.0f;
  unsigned int width = 500;
  unsigned int height = 500;
  float aspectRatio = width / height;
  float fov = 70.0f;
  mb::Camera camera( fov, aspectRatio, near, far );

  auto proj1 = camera.getFrustum( ).computeProjMatrix( );
  auto proj2 = Matrix4::perspective( fov, aspectRatio, near, far );

  BOOST_CHECK_EQUAL( proj1, proj2 );
}
BOOST_AUTO_TEST_CASE( test_camera_frustum )
{
  float near = 0.01f;
  float far = 1000.0f;
  unsigned int width = 500;
  unsigned int height = 500;
  float aspectRatio = width / height;
  float fov = 70.0f;
  mb::Camera camera( fov, aspectRatio, near, far );

  BOOST_CHECK_EQUAL( camera.getFrustum( ).getAspect( ), aspectRatio );
  BOOST_CHECK_EQUAL( camera.getFrustum( ).getLinearDepth( ), far - near );
}

BOOST_AUTO_TEST_CASE( test_camera_fetch )
{
  auto group = new Group( "" );
  auto camera = new Camera( );
  group->addChild( camera );

  mb::FetchCameras fc;
  group->perform( fc );
  fc.forEachCameras([&]( mb::Camera* cc )
  {
    BOOST_CHECK_EQUAL( cc, camera );
  });
}
