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

class ExplosionComponent : public mb::Component
{
  IMPLEMENT_COMPONENT( ExplosionComponent )
public:
  ExplosionComponent( )
    : mb::Component( )
    , _globalTime( 0.0f )
  {
  }
  virtual void start( void ) override
  {
    _material = node( )->getComponent< mb::MaterialComponent >( )->first( );
    _material->uniform( "time" )->value( _globalTime );
  }
  virtual void update( const mb::Clock& c ) override
  {
    _globalTime += c.getDeltaTime( );
    _material->uniform( "time" )->value( _globalTime );
  }
protected:
  float _globalTime;
  mb::MaterialPtr _material;
};

mb::Material* createMaterial( )
{
  mb::Material* customMaterial = new mb::Material( );

  customMaterial->program->loadVertexShaderFromText( R"(
    #version 430
    layout(location = 0) in vec3 position;
    layout(location = 2) in vec2 texCoords;
    out VS_OUT
    {
      vec2 texCoords;
    } vs_out;
    uniform mat4 MB_MATRIXP;
    uniform mat4 MB_MATRIXV;
    uniform mat4 MB_MATRIXM;
    void main( void )
    {
      gl_Position = MB_MATRIXP * MB_MATRIXV * MB_MATRIXM * vec4(position, 1.0f);
      vs_out.texCoords = texCoords;
    })" );
  customMaterial->program->loadGeometryShaderFromText( R"(
    #version 430
    layout (triangles) in;
    layout (triangle_strip, max_vertices = 3) out;
    in VS_OUT
    {
      vec2 texCoords;
    } gs_in[];
    out vec2 TexCoords;
    out vec3 color;
    uniform float time;
    vec4 explode(vec4 position, vec3 normal)
    {
      float magnitude = 5.0f;
      if (gl_PrimitiveIDIn % 3 == 0)
      {
        vec3 direction = normal * ((sin(time) + 1.0f) / 2.0f) * magnitude;
        color = vec3( 1.0, 0.0, 0.0 );
        return position + vec4(direction, 0.0f);
      }
      else if (gl_PrimitiveIDIn % 3 == 1)
      {
        vec3 direction = normal * ((cos(time) + 1.0f) / 2.0f) * magnitude;
        color = vec3( 0.0, 1.0, 0.0 );
        return position + vec4(direction, 0.0f);
      }
      else
      {
        vec3 direction = normal * ((tan(time) + 1.0f) / 2.0f) * magnitude;
        color = vec3( 0.0, 0.0, 1.0 );
        return position + vec4(direction, 0.0f);
      }
    }
    vec3 GetNormal()
    {
      vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
      vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
      return normalize(cross(a, b));
    }
    void main( void )
    {
      vec3 normal = GetNormal();
      gl_Position = explode(gl_in[0].gl_Position, normal);
      TexCoords = gs_in[0].texCoords;
      EmitVertex();
      gl_Position = explode(gl_in[1].gl_Position, normal);
      TexCoords = gs_in[1].texCoords;
      EmitVertex();
      gl_Position = explode(gl_in[2].gl_Position, normal);
      TexCoords = gs_in[2].texCoords;
      EmitVertex();
      EndPrimitive();
    })" );
  customMaterial->program->loadFragmentShaderFromText( R"(
    #version 430
    out vec4 fragColor;
    in vec3 color;
    void main( void )
    {
      fragColor = vec4(color, 1.0);
    })" );
  customMaterial->program->compileAndLink( );
  customMaterial->program->autocatching( );

  customMaterial->addStandardUniforms( );
  customMaterial->addUniform( "time", std::make_shared< mb::FloatUniform >( 0.0f ) );

  customMaterial->state( ).culling( ).setEnabled( false );

  return customMaterial;
}

mb::Geometry* generateGeom( const mb::Color& )
{
  auto geom = new mb::Geometry( );

  geom->addPrimitive( new mb::SpherePrimitive( 5.0f, 100, 100 ) );

  mb::Material* customMaterial = createMaterial( );

  mb::MaterialComponent* mc = geom->getComponent<mb::MaterialComponent>( );
  mc->addMaterial( mb::MaterialPtr( customMaterial ) );

  geom->addComponent( new ExplosionComponent( ) );

  geom->addComponent( new mb::RotateComponent( mb::Vector3::X_AXIS, 0.05f ) );

  return geom;
}

mb::Group* createScene( void )
{
  auto scene = new mb::Group( "scene" );

  auto camera = new mb::Camera( 45.0f, 500 / 500, 0.01f, 1000.0f );
  camera->local( ).translate( 0.0f, 0.0f, 25.0f );

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
  window->setTitle( "Explosion Demo" );

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
