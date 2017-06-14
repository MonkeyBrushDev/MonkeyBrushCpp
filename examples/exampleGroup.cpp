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
using namespace mb;

int main( )
{
  auto scene = new Scene( "scene" );

  auto node0 = new Group( "node0" );
  auto node2 = new Group( "node2" );
  auto node1 = new Node( "node1" );
  auto node3 = new Node( "node3" );
  auto node4 = new Node( "node4" );

  node0->addChild( node1 );
  node0->addChild( node2 );
  node2->addChild( node3 );
  node2->addChild( node4 );

  scene->addChild( node0 );

  auto camera = new Camera( );
  scene->addChild( camera );

  mb::DumpVisitor dv;
  dv.traverse( scene );

  App app;
  app.setSceneNode( scene );
  app.run( );
  delete scene;
  system( "PAUSE" );
  return 0;
}
