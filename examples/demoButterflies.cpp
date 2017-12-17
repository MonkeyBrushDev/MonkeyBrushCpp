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

#define MAXPOINTS 500		// Change this to increment num of points
#define RANDOM_POINT 0.02

std::vector< mb::Vector3 > createPoints( void )
{
  srand( time( NULL ) );
  std::vector< mb::Vector3 > points( MAXPOINTS );
  for ( int i = 0; i < MAXPOINTS; ++i )
  {
    points[ i ].x( ) = ( ( float ) ( std::rand( ) % 1000 ) ) * RANDOM_POINT;
    points[ i ].y( ) = ( ( float ) ( std::rand( ) % 1000 ) ) * RANDOM_POINT;
    points[ i ].z( ) = ( ( float ) ( std::rand( ) % 1000 ) ) * RANDOM_POINT;
  }

  return points;
}

class ButterfliesUpdaterComponent : public mb::Component
{
  IMPLEMENT_COMPONENT( ButterfliesUpdaterComponent )
public:
  virtual void start( void ) override
  {
    _material = node( )->getComponent< mb::MaterialComponent >( )->first( );
  }
  virtual void update( const mb::Clock& clock )
  {
    _material->uniform( "time" )->value( ( float ) clock.getAccumTime( ) );
    _material->uniform( "up" )->value( 0.01f * ( float ) sin( clock.getAccumTime( ) ) );
    _material->uniform( "beta" )->value( ( float ) mb::Mathf::degToRad( -45.0f ) );
  }
protected:
  mb::MaterialPtr _material;
};

std::shared_ptr<mb::Program> createProgram( std::shared_ptr<mb::Program> program )
{
  program->loadVertexShaderFromText( R"(
  #version 430
  layout (location = 0) in vec3 position;

  uniform float time;
  uniform float up;

  const vec3 vel = vec3( up, 0.1, 0.0 );

  void main( )
  {
     vec3 pos = position + vel * time; // x = x0 + dt * v;
     gl_Position = vec4(pos, 1.0);
  })" );
  program->loadGeometryShaderFromText( R"(
    #version 430
    layout (points) in;
    layout (triangle_strip, max_vertices = 8) out;

    out vec2 TexCoord;

    uniform float time;
    uniform float beta;

    uniform mat4 MB_MATRIXM;
    uniform mat4 MB_MATRIXV;
    uniform mat4 MB_MATRIXP;

    #define PI 3.1415

    vec2 size = vec2(1.0, 2.0);

    void generateQuad(in mat4 Transf, int sign) {
	    vec4 Position = gl_in[0].gl_Position;
	    gl_Position = Position;
	    gl_Position.xy += vec2(sign * size.x, -size.y / 2.0);
	    gl_Position = Transf * gl_Position;
	    TexCoord = vec2(0.0, 0.0);
	    EmitVertex();

	    gl_Position = Position;
	    gl_Position.xy += vec2(sign * size.x, size.y / 2.0);
	    gl_Position = Transf * gl_Position;
	    TexCoord = vec2(0.0, 1.0);
	    EmitVertex();
	    gl_Position = Position;
	    gl_Position.xy += vec2(0.0, -size.y / 2.0);
	    gl_Position = Transf * gl_Position;
	    TexCoord = vec2(1.0, 0.0);
	    EmitVertex();
	    gl_Position = Position;
	    gl_Position.xy += vec2(0.0, size.y / 2.0);
	    gl_Position = Transf * gl_Position;
	    TexCoord = vec2(1.0, 1.0);
	    EmitVertex();

	    EndPrimitive();
    }

    void main()  {
      mat4 modelViewProj = MB_MATRIXP * MB_MATRIXV * MB_MATRIXM;
	    vec4 Position = gl_in[0].gl_Position;
	    // Alpha: Aperture quad angle.
	    float alpha = radians(-65.0) + 0.9*abs(sin(time));

	    // Translate quad to origin
	    mat4 Tgo = mat4(
		    vec4(1.0, 0.0, 0.0, 0.0),
		    vec4(0.0, 1.0, 0.0, 0.0),
		    vec4(0.0, 0.0, 1.0, 0.0),
		    vec4(-Position.xyz, 1.0));

	    // Translate quad to original position
	    mat4 Tini = mat4(
		    vec4(1.0, 0.0, 0.0, 0.0),
		    vec4(0.0, 1.0, 0.0, 0.0),
		    vec4(0.0, 0.0, 1.0, 0.0),
		    vec4(Position.xyz, 1.0));

	    // Rotate quads with Y axis rotation. Give appearance of moving quads (left quad)
	    mat4 RotQ = mat4(
		    vec4(cos(alpha), 0.0, -sin(alpha), 0.0),
		    vec4(0.0, 1.0, 0.0, 0.0),
		    vec4(sin(alpha), 0.0, cos(alpha), 0.0),
		    vec4(0.0, 0.0, 0.0, 1.0));

	    // Rotate quads with Z axis rotation. "Flying" direction
	    mat4 RotZ = mat4(
		    vec4(cos(beta), sin(beta), 0.0, 0.0),
		    vec4(-sin(beta), cos(beta), 0.0, 0.0),
		    vec4(0.0, 0.0, 1.0, 0.0),
		    vec4(0.0, 0.0, 0.0, 1.0));

	    // Final transform matrix
	    mat4 Transf = modelViewProj * RotZ * Tini * RotQ * Tgo;

	    // Generate quad from original point´s position. Finally transform with Transf matrix.
	    generateQuad(Transf, -1);

	    // Alpha: Aperture angle for simetric quad
	    alpha = PI - alpha;
	    // Rotate quads with Y axis rotation. Give appearance of moving quads (right quad)
	    RotQ = mat4(
		    vec4(cos(alpha), 0.0, -sin(alpha), 0.0),
		    vec4(0.0, 1.0, 0.0, 0.0),
		    vec4(sin(alpha), 0.0, cos(alpha), 0.0),
		    vec4(0.0, 0.0, 0.0, 1.0));

	    Transf = modelViewProj * RotZ * Tini * RotQ * Tgo;
	    generateQuad(Transf, 1);
    })" );
  program->loadFragmentShaderFromText( R"(
    #version 430
    in vec2 TexCoord;
    out vec4 fragColor;

    uniform sampler2D image;

    const vec3 fogColor = vec3( 0.2, 0.3, 0.3 );
    const vec3 color = vec3( 1.0, 0.3, 0.4 );

    void main()
    {
		  vec4 tex = texture(image, TexCoord).rgba;
		  if(tex.a < 0.4) discard;
		  fragColor = vec4(tex);
    })" );
  program->compileAndLink( );
  program->autocatching( );

  return program;
}

mb::Geometry* generateGeom( void )
{
  auto geom = new mb::Geometry( );
  geom->addPrimitive( new mb::PointCloudPrimitive( createPoints( ) ) );

  mb::Material* customMaterial = new mb::Material( );
  customMaterial->program = createProgram( customMaterial->program );

  customMaterial->addStandardUniforms( );
  customMaterial->addUniform( "time",
    std::make_shared< mb::FloatUniform >( ) );
  customMaterial->addUniform( "up",
    std::make_shared< mb::FloatUniform >( ) );
  customMaterial->addUniform( "beta",
    std::make_shared< mb::FloatUniform >( ) );

  mb::Texture2D* TexDiffuse = mb::Texture2D::loadFromImage( "butterfly.png" );
  customMaterial->addUniform( "image",
    std::make_shared< mb::TextureUniform >( TexDiffuse ) );

  customMaterial->state( ).culling( ).setEnabled( false );

  mb::MaterialComponent* mc = geom->getComponent<mb::MaterialComponent>( );
  mc->addMaterial( mb::MaterialPtr( customMaterial ) );

  geom->addComponent( new ButterfliesUpdaterComponent( ) );

  return geom;
}

mb::Group* createScene( void )
{
  auto scene = new mb::Group( "scene" );

  auto camera = new mb::Camera( 60.0f, 500 / 500, 0.01f, 1000.0f );
  camera->local( ).translate( 25.0f, 0.0f, 25.0f );

  auto node = generateGeom( );

  scene->addChild( node );

  camera->addComponent( new mb::FreeCameraComponent( ) );
  scene->addChild( camera );

  return scene;
}

int main( void )
{
  mb::FileSystem::getInstance( )->setBaseDirectory( MB_EXAMPLES_RESOURCES_ROUTE );

  mb::Window* window = new mb::GLFWWindow2( mb::WindowParams( 500, 500 ) );
  window->init( );

  window->setTitle( "Butterflies" );

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

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    app.update( );

    window->swapBuffers( );
  }
  return 0;

}

