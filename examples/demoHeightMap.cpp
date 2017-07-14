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

class HeightMapMaterial : public mb::Material
{
public:
  HeightMapMaterial( void )
    : mb::Material( )
  {
    program = std::make_shared< mb::Program >( );

    const char* vsShader = R"(#version 330
      layout(location = 0) in vec3 position;
      layout(location = 1) in vec3 normal;
      layout(location = 2) in vec2 uv;

      out vec2 outUV;

      uniform mat4 MB_MATRIXP;
      uniform mat4 MB_MATRIXV;
      uniform mat4 MB_MATRIXM;
      uniform float amount;
      uniform sampler2D tex;
      void main( void )
      {
        mat3 normalMatrix = mat3(inverse(transpose(MB_MATRIXM)));
        vec3 pos = position;
        outUV = uv;
        const vec2 size = vec2(0.5, 0.0);
        const ivec3 off = ivec3(-1, 0, 1);
        vec4 wave = texture(tex, outUV);
        float s11 = wave.x;
        float s01 = textureOffset(tex, outUV, off.xy).x;
        float s21 = textureOffset(tex, outUV, off.zy).x;
        float s10 = textureOffset(tex, outUV, off.yx).x;
        float s12 = textureOffset(tex, outUV, off.yz).x;
        vec3 va = normalize(vec3(size.xy, s21 - s01));
        vec3 vb = normalize(vec3(size.yx, s12 - s10));
        vec4 bump = vec4(cross(va, vb), s11);
        pos.z += amount * bump.w;
        vec4 pp = MB_MATRIXM * vec4(pos, 1.0);
        pp = MB_MATRIXV * pp;
        gl_Position = MB_MATRIXP * pp;
      })";
    const char* fsShader = R"(#version 330
      in vec2 outUV;
      uniform sampler2D tex;
      out vec4 fragColor;
      void main( void )
      {
        fragColor = texture(tex, outUV);
      };)";
    program->loadFromText( vsShader, fsShader );
    program->compileAndLink( );
    program->autocatching( );

    this->addStandardUniforms( );

    this->addUniform( "tex", std::make_shared< mb::TextureUniform >( ) );
    this->addUniform( "amount", std::make_shared< mb::FloatUniform >( 1.0f ) );
  }
};

class HeightMapController : public mb::Component
{
  IMPLEMENT_COMPONENT( HeightMapController )
public:
  HeightMapController( const float& amount )
    : mb::Component( )
    , _amount( amount )
  {
  }
  virtual void start( void ) override
  {
    _material = node( )->getComponent< mb::MaterialComponent >( )->first( );
    _material->uniform( "amount" )->value( _amount );
  }
  virtual void update( const mb::Clock& ) override
  {
    if ( mb::Input::isKeyPressed( mb::Keyboard::Key::Plus ) )
    {
      _amount -= 0.1f;
      _material->uniform( "amount" )->value( _amount );
    }
    if ( mb::Input::isKeyPressed( mb::Keyboard::Key::Minus ) )
    {
      _amount += 0.1f;
      _material->uniform( "amount" )->value( _amount );
    }
  }
protected:
  float _amount;
  mb::MaterialPtr _material;
};

mb::Geometry* generateGeom( const mb::Color& )
{
  auto geom = new mb::Geometry( );

  geom->local( ).setRotation( mb::Vector3::X_AXIS, -45.0f );

  geom->addPrimitive( new mb::PlanePrimitive( 26.0f, 20.0f, 200, 200 ) );

  mb::Material* customMaterial = new HeightMapMaterial( );

  //customMaterial->state( ).culling( ).setEnabled( false );
  //customMaterial->state( ).wireframe( )->setEnabled( true );

  mb::Texture2D* Tex = mb::Texture2D::loadFromImage( "heightmap.jpg" );
  customMaterial->uniform( "tex" )->value( Tex );

  mb::MaterialComponent* mc = geom->getComponent<mb::MaterialComponent>( );
  mc->addMaterial( mb::MaterialPtr( customMaterial ) );

  geom->addComponent( new HeightMapController( 5.0f ) );
  //geom->addComponent( new mb::RotateComponent( mb::Vector3::ONE, 0.25f ) );

  return geom;
}

mb::Group* createScene( void )
{
  auto scene = new mb::Group( "scene" );

  auto camera = new mb::Camera( 45.0f, 500 / 500, 0.01f, 1000.0f );
  camera->local( ).translate( 0.0f, 0.0f, 10.0f );

  scene->addChild( generateGeom( mb::Color::GREY ) );

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

  app.init( );

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
