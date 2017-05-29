#include "mbTests.h"
#include <mb/mb.h>

using namespace mb;

BOOST_AUTO_TEST_CASE( test_vector_construction )
{
  mb::Vector3 v( 1.0f );
  BOOST_CHECK_EQUAL( v.x( ), 1.0f );
  BOOST_CHECK_EQUAL( v.y( ), 1.0f );
  BOOST_CHECK_EQUAL( v.z( ), 1.0f );
}

BOOST_AUTO_TEST_CASE( test_vector_add )
{
  mb::Vector3 u( 2.0f );
  mb::Vector3 v( 4.0f );
  mb::Vector3 w = u + v;
  BOOST_CHECK_EQUAL( w.x( ), 6.0f );
  BOOST_CHECK_EQUAL( w.y( ), 6.0f );
  BOOST_CHECK_EQUAL( w.z( ), 6.0f );
}

BOOST_AUTO_TEST_CASE( test_vector_rem )
{
  mb::Vector3 u( 2.0f );
  mb::Vector3 v( 4.0f );
  mb::Vector3 w = u - v;
  BOOST_CHECK_EQUAL( w.x( ), -2.0f );
  BOOST_CHECK_EQUAL( w.y( ), -2.0f );
  BOOST_CHECK_EQUAL( w.z( ), -2.0f );
}

BOOST_AUTO_TEST_CASE( test_vector_negative )
{
  mb::Vector3 u( 2.0f );
  mb::Vector3 w = -u;
  BOOST_CHECK_EQUAL( w.x( ), -2.0f );
  BOOST_CHECK_EQUAL( w.y( ), -2.0f );
  BOOST_CHECK_EQUAL( w.z( ), -2.0f );
}

BOOST_AUTO_TEST_CASE( test_vector_times )
{
  mb::Vector3 u( 1.0f, 2.0f, 3.0f );
  u.times( 2.0f );
  BOOST_CHECK_EQUAL( u.x( ), 2.0f );
  BOOST_CHECK_EQUAL( u.y( ), 4.0f );
  BOOST_CHECK_EQUAL( u.z( ), 6.0f );
}

BOOST_AUTO_TEST_CASE( test_vector_normalize )
{
  Vector3 u( 2.0f, 4.0f, 6.0f );
  Vector3 v = u;

  v.normalize( );

  BOOST_CHECK_EQUAL( v, u / u.getMagnitude( ) );

  // TODO: BOOST_CHECK_EQUAL( v.getMagnitude(), 1.0f );
  BOOST_CHECK_EQUAL( v.x( ), u.x( ) / u.getMagnitude() );
  BOOST_CHECK_EQUAL( v.y( ), u.y( ) / u.getMagnitude() );
  BOOST_CHECK_EQUAL( v.z( ), u.z( ) / u.getMagnitude() );
}

BOOST_AUTO_TEST_CASE( test_vector_cross )
{
  mb::Vector3 u( 3.0f, -3.0f, 1.0f );
  mb::Vector3 v( 4.0f, 9.0f, 2.0f );
  mb::Vector3 w = u ^ v;

  BOOST_CHECK_EQUAL( w.x( ), -15.0f );
  BOOST_CHECK_EQUAL( w.y( ),  -2.0f );
  BOOST_CHECK_EQUAL( w.z( ),  39.0f );

  u = mb::Vector3( 3.0f, -3.0f, 5.0f );
  v = u * 2.0f;

  w = mb::Vector3::cross( u, v );

  BOOST_CHECK_EQUAL( w, mb::Vector3::ZERO );
}
