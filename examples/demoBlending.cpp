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

class BlendingController : public mb::Component
{
  IMPLEMENT_COMPONENT( BlendingController )
public:
  BlendingController( void )
    : mb::Component( )
  { }
  virtual void start( void ) override
  {
    _material = node( )->getComponent< mb::MaterialComponent >( )->first( );
    _material->state( ).culling( ).setEnabled( false );
    //_material->state( ).blending( ).setEnabled( true );
    _material->state( ).blending( ).setBlendType( mb::PipelineState::BlendingState::Type::Normal );
  }
  virtual void update( const mb::Clock& ) override
  {
    if ( mb::Input::isKeyPressed( mb::Keyboard::Key::Num1 ) )
    {
      _material->state( ).blending( ).setBlendType( mb::PipelineState::BlendingState::Type::None );
    }
    else if ( mb::Input::isKeyPressed( mb::Keyboard::Key::Num2 ) )
    {
      _material->state( ).blending( ).setBlendType( mb::PipelineState::BlendingState::Type::Normal );
    }
    else if ( mb::Input::isKeyPressed( mb::Keyboard::Key::Num3 ) )
    {
      _material->state( ).blending( ).setBlendType( mb::PipelineState::BlendingState::Type::Additive );
    }
    else if ( mb::Input::isKeyPressed( mb::Keyboard::Key::Num4 ) )
    {
      _material->state( ).blending( ).setBlendType( mb::PipelineState::BlendingState::Type::Substractive );
    }
    else if ( mb::Input::isKeyPressed( mb::Keyboard::Key::Num5 ) )
    {
      _material->state( ).blending( ).setBlendType( mb::PipelineState::BlendingState::Type::Multiply );
    }
  }
protected:
  float _amount;
  mb::MaterialPtr _material;
};

mb::Geometry* generateGeom( void )
{
  auto geom = new mb::Geometry( );

  geom->addPrimitive( new mb::CubePrimitive( ) );

  mb::ColorMaterial* customMaterial = new mb::ColorMaterial( );
  customMaterial->setColor( mb::Color(1.0f, 1.0f, 1.0, 0.5f ) );
  mb::Texture2D* TexDiffuse = mb::Texture2D::loadFromImage( "uv_checker.png" );
  customMaterial->setColorMap( TexDiffuse );

  mb::MaterialComponent* mc = geom->getComponent<mb::MaterialComponent>( );
  mc->addMaterial( mb::MaterialPtr( customMaterial ) );

  geom->addComponent( new mb::RotateComponent( mb::Vector3::ONE, 0.15f ) );
  geom->addComponent( new BlendingController( ) );

  return geom;
}

mb::Group* createScene( void )
{
  auto scene = new mb::Group( "scene" );

  auto camera = new mb::Camera( 45.0f, 500 / 500, 0.01f, 1000.0f );
  camera->local( ).translate( 0.0f, 0.0f, 10.0f );

  scene->addChild( generateGeom( ) );

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
