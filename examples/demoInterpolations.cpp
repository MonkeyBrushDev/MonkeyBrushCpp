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
#include <string>

#include <mb/mb.h>
#include <routes.h>

#include "others/FogShader.hpp"

mb::Material* createFogMaterial( )
{
  mb::Material* customMaterial = new mb::Material( );

  customMaterial->program = std::make_shared< mb::Program >( );
  customMaterial->program->loadVertexShaderFromText( VS_FOG_SHADER );
  customMaterial->program->loadFragmentShaderFromText( FS_FOG_SHADER );
  customMaterial->program->compileAndLink( );
  customMaterial->program->autocatching( );

  customMaterial->addStandardUniforms( );
  customMaterial->addUniform( "density",
    std::make_shared< mb::FloatUniform >( 0.04f ) );

  return customMaterial;
}

#include <map>

class EaseFunction : public mb::Component
{
  IMPLEMENT_COMPONENT( EaseFunction )
public:
  EaseFunction( )
  {
    functions[ "sine" ] = mb::easing::sine::easeInOut;
    functions[ "quad" ] = mb::easing::quad::easeInOut;
    functions[ "cubic" ] = mb::easing::cubic::easeInOut;
    functions[ "quart" ] = mb::easing::quart::easeInOut;
    functions[ "quint" ] = mb::easing::quint::easeInOut;
    functions[ "expo" ] = mb::easing::expo::easeInOut;
    functions[ "circ" ] = mb::easing::circ::easeInOut;
    functions[ "back" ] = mb::easing::back::easeInOut;
    functions[ "elastic" ] = mb::easing::elastic::easeInOut;
    functions[ "bounce" ] = mb::easing::bounce::easeInOut;
    it = functions.begin( );
  }
  virtual void update( const mb::Clock& clock )
  {
    float new_y = it->second( _time ) * 1.0f;

    mb::Vector3 pos = node()->local().getPosition( );
    pos.y( ) = new_y;

    node( )->local( ).setPosition( pos );
    _time += 0.25f * clock.getDeltaTime( );

    if ( _time > 1.0f )
    {
      ++it;
      if ( it == functions.end( ) )
      {
        it = functions.begin( );
      }
      std::cout << "Change to " << it->first << std::endl;
      _time = 0.0f;
    }
    std::cout << _time << " - " << it->first << std::endl;
  }
protected:
  float _time = 0.0f;
  std::map< std::string, std::function< float( float ) > >::iterator it;
  std::map< std::string, std::function< float( float ) > > functions;
};

mb::Geometry* generateGeom( const mb::Color& )
{
  auto geom = new mb::Geometry( );

  geom->addPrimitive( new mb::SpherePrimitive( 5.0f, 25, 25 ) );

  mb::Material* customMaterial = createFogMaterial( );

  mb::MaterialComponent* mc = geom->getComponent<mb::MaterialComponent>( );
  mc->addMaterial( mb::MaterialPtr( customMaterial ) );

  geom->addComponent( new EaseFunction( ) );
  //geom->addComponent( new mb::RotateComponent( mb::Vector3::ONE, 0.25f ) );

  return geom;
}

mb::Group* createScene( void )
{
  auto scene = new mb::Group( "scene" );

  auto camera = new mb::Camera( 45.0f, 500 / 500, 0.01f, 1000.0f );
  camera->local( ).translate( 0.0f, 0.0f, 15.0f );

  auto node = generateGeom( mb::Color::GREY );

  scene->addChild( node );

  camera->addComponent( new mb::FreeCameraComponent( ) );
  scene->addChild( camera );

  return scene;
}

int main( )
{
  mb::FileSystem::getInstance( )->setBaseDirectory( MB_EXAMPLES_RESOURCES_ROUTE );

  mb::Window* window = new mb::GLFWWindow2( mb::WindowParams( 500, 500 ) );
  window->init( );
  window->setTitle( "Fog Demo" );

  mb::Application app;

  app.setSceneNode( createScene( ) );

  app.init( ); // initialize settings to render the scene...

  while ( window->isRunning( ) )
  {
    window->pollEvents( );

    if ( mb::Input::isKeyPressed( mb::Keyboard::Key::Esc ) )
    {
      window->close( );
      break;
    }

    app.update( );

    window->swapBuffers( );
  }
  return 0;
}
