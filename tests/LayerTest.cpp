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
