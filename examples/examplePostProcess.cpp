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

  auto geom = new Geometry( "nodeGeom" );
  geom->addPrimitive( new Primitive( ) );
  scene->addChild( geom );
  geom->layer( ).set( 2 );

  auto camera = new Camera( );
  camera->name( "PPCamera" );
  camera->renderPass( new PostRenderingPass( new StandardRenderingPass( ) ) );
  camera->renderPass( )->imageEffects( ).push_back( 
    std::make_shared< SepiaToneEffect >( ) );
  camera->renderPass( )->imageEffects( ).push_back( 
    std::make_shared<  GreyToneEffect>( ) );
  scene->addChild( camera );

  camera->layer( ).enable( 1 );
  camera->layer( ).enable( 2 );
  camera->layer( ).enable( 3 );

  mb::DumpVisitor dv;
  dv.traverse( scene );

  App app;
  app.setSceneNode( scene );
  app.run( );

  /*std::cout << std::endl << std::endl << std::endl;

  geom->layer( ).set( 4 );
  e.run( );*/
  delete scene;
  system( "PAUSE" );
  return 0;
}
