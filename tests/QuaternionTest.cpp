#include "mbTests.h"
#include <mb/mb.h>

using namespace mb;

BOOST_AUTO_TEST_CASE( test_quaternion_construction )
{
  Quaternion q( 0.0f, 1.0f, 2.0f, 3.0f );
  BOOST_CHECK_EQUAL( q.x( ), 0.0f );
  BOOST_CHECK_EQUAL( q.y( ), 1.0f );
  BOOST_CHECK_EQUAL( q.z( ), 2.0f );
  BOOST_CHECK_EQUAL( q.w( ), 3.0f );
}

BOOST_AUTO_TEST_CASE( test_identity )
{
  Quaternion q( 0.0f, 1.0f, 2.0f, 3.0f );
  q.makeIdentity( );
  BOOST_CHECK_EQUAL( q.x( ), 0.0f );
  BOOST_CHECK_EQUAL( q.y( ), 0.0f );
  BOOST_CHECK_EQUAL( q.z( ), 0.0f );
  BOOST_CHECK_EQUAL( q.w( ), 1.0f );
}
