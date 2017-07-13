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

int main( )
{
  mb::xml_document doc;
  mb::xml_parse_result result = doc.load_file( "C:\\Users\\maldicion069\\Desktop\\clonclon\\scene.xml" );
  //doc.LoadFile( "C:\\Users\\maldicion069\\Desktop\\clonclon\\scene.xml" );
  if ( result )
  {
    auto app = doc.child( "app" );
    std::cout << app.attribute( "title" ).value( ) << std::endl;
    auto objects = app.child( "objects" );
    for ( mb::xml_node obj = objects.child( "object" ); obj; obj = obj.next_sibling( "object" ) )
    {
      std::cout << "OBJECT: " << obj.attribute( "name" ).value( ) << std::endl;
      auto transf = obj.child( "transform" );

      auto pos = transf.attribute( "position" );
      auto rot = transf.attribute( "rotation" );
      auto quat = transf.attribute( "quaternion" );
      auto scale = transf.attribute( "scale" );

      std::string str = pos.value( );

      std::cout << "TRANSFORM: Position(" << pos.value( ) << ")" << std::endl;

      auto components = obj.child( "components" );
      for ( auto comp = components.child( "component" ); comp; comp = comp.next_sibling( "component" ) )
      {
        std::cout << "COMPONENT: " << comp.attribute( "name" ).value( ) << std::endl;
        if ( comp.attribute( "name" ).value( ) == std::string( "RotateComponent" ) )
        {
          auto aux = comp.child( "axis" );
          auto axis = aux.value( );
          auto rotate = comp.child( "rotate" ).value( );
          std::cout << "AXIS: " << comp.child( "axis" ).value( ) << std::endl;
          std::cout << "rotate: " << rotate << std::endl;
        }
      }
    }
  }
  system( "PAUSE" );
  return 0;
}
