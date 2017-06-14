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

#include <iostream>
#include <mb/mb.h>
#include <string>
#include <assert.h>
#include <routes.h>
using namespace mb;

int main( )
{
  /*mb::concurrency::JobScheduler::getInstance( )->configure( 0 );
  mb::concurrency::JobScheduler::getInstance( )->start( );
  auto job = mb::concurrency::async( );
  for ( int i = 0; i < 10; ++i )
  {
    mb::concurrency::async( job, [ &]
    {
      std::this_thread::sleep_for( std::chrono::milliseconds( 1234 ) );
      std::cout << "EVENTO: " << i << std::endl;
    } );
  }
  std::cout << "WAIT" << std::endl;
  mb::concurrency::wait( job );
  std::cout << "FIN" << std::endl;*/

  mb::concurrency::JobScheduler jobScheduler;
  jobScheduler.configure( );
  jobScheduler.start( );

  auto parent = mb::concurrency::async( );
  std::atomic< int > counter( 0 );
  for ( int i = 0; i < 400; ++i )
  {
    auto child = mb::concurrency::async( parent, [ &counter ] ( )
    {
      ++counter;
    } );
  }

  mb::concurrency::wait( parent );
  
  jobScheduler.stop( );

  system( "PAUSE" );
  return 0;
}
