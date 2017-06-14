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

  auto geom = new Geometry( "geom" );
  geom->addPrimitive( new Primitive( ) );
  scene->addChild( geom );

  auto interactiveLight = new Group( "InteractiveLight" );
  auto lightGeometry = new Geometry( "LightGeometry" );
  lightGeometry->addPrimitive( new Primitive( ) );

  auto mr = lightGeometry->getComponent<mb::MaterialComponent>( );
  auto material = mr->first( );
  material->state( ).culling( ).setEnabled( true );

  std::cout << lightGeometry->hasComponent<mb::MaterialComponent>( ) << std::endl;

  auto light = new Light( );
  interactiveLight->addChild( lightGeometry );
  interactiveLight->addChild( light );

  scene->addChild( interactiveLight );

  auto cam = new Camera( );
  Camera::setMainCamera( cam );
  scene->addChild( cam );
  cam->local( ).translate( 0.0f, 1.0f, 0.0f );

  mb::DumpVisitor dv;
  dv.traverse( scene );

  App app;
  app.setSceneNode( scene );
  app.run( );
  delete scene;

  system( "PAUSE" );
  return 0;
}
