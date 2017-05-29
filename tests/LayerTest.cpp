#include "mbTests.h"
#include <mb/mb.h>

using namespace mb;

BOOST_AUTO_TEST_CASE( test_layers_lookup )
{
  std::string layerName = std::string( "RandomLayer" );
  mb::LayerLookup::setName( layerName, 5 );
  BOOST_CHECK_EQUAL( layerName, mb::LayerLookup::getName( 5 ) );
  ///mb::Layer
  // mb::Primitive p;
  // mb::Primitive p2( mb::Primitive::Type::POINTS) ;
  // BOOST_CHECK_EQUAL( );
}
