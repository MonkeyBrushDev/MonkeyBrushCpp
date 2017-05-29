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
