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
  auto leftNode = new Node( "leftNode" );
  auto centerSwitch = new Switch( "centerSwitch" );
  auto rightNode = new Node( "rightNode" );

  scene->addChild( leftNode );
  scene->addChild( centerSwitch );

  auto firstNodeSwitch = new Node( "firstNodeSwitch" );
  auto secondNodeSwitch = new Group( "secondNodeSwitch" );
  secondNodeSwitch->addChild( new Node( "firstSecondNodeSwitch" ) );
  auto thirdNodeSwitch = new Node( "thirdNodeSwitch" );
  secondNodeSwitch->addChild( rightNode );

  centerSwitch->addChild( firstNodeSwitch );
  centerSwitch->addChild( secondNodeSwitch );
  centerSwitch->addChild( thirdNodeSwitch );

  leftNode->addComponent( new MeshRenderer( ) );
  secondNodeSwitch->addComponent( new MeshRenderer( ) );
  secondNodeSwitch->addChild( new Node( "RandomNodeFromSecondSwitch" ) );
  //rightNode->addComponent( new MeshRenderer( 2 ) );

  centerSwitch->setCurrentNodeIndex( 0 );

  /*PrintNameVisitor v;
  v.visitGroup( scene );

  FetchGeometry fv( 2 );
  fv.traverse( scene );
  std::cout << fv.rq.size( ) << std::endl;
  FetchGeometry fv2( 3 );
  fv2.traverse( scene );
  std::cout << fv2.rq.size( ) << std::endl;*/

  /*ChildrenCounterVisitor ccv;
  ccv.traverse( scene );
  std::cout << ccv._childrens << std::endl;*/



  /*centerSwitch->currentNodeIndex( 0 );

  ChildrenCounterVisitor ccv2;
  ccv2.traverse( scene );
  std::cout << ccv2._childrens << std::endl;*/

  mb::DumpVisitor dv;

  App app;
  app.setSceneNode( scene );

  for ( unsigned int i = 0, l = centerSwitch->numChildren( ); i < l; ++i )
  {
    dv.traverse( scene );
    app.run( );
    if ( i > 0 )
    {
      std::cout << std::endl << std::endl << std::endl;
    }
    centerSwitch->setCurrentNodeIndex( i );
  }

  delete scene;
  system( "PAUSE" );
}
