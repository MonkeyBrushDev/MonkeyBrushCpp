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

#include "FetchCameras.hpp"

namespace mb
{
  void FetchCameras::reset( void )
  {
    _cameras.clear( );
    Visitor::reset( );
  }

  void FetchCameras::visitCamera( Camera *c )
  {
    _cameras.push_back( c );
  }

  void FetchCameras::forEachCameras( std::function< void( Camera * ) > cb )
  {
    for ( auto& camera : _cameras ) {
      cb( camera );
    }
    _cameras.clear( );
  }
}
