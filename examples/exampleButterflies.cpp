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

unsigned int vao;
#define MAXPOINTS 500		// Change this to increment num of points
#define RANDOM_POINT 0.02
unsigned int createVAO( )
{
  srand( time( NULL ) );
  GLfloat points[ MAXPOINTS * 3 ];
  for ( int i = 0; i < MAXPOINTS * 3; i += 3 )
  {
    points[ i ] = ( ( float ) ( std::rand( ) % 1000 ) ) * RANDOM_POINT;
    points[ i + 1 ] = ( ( float ) ( std::rand( ) % 1000 ) ) * RANDOM_POINT;
    points[ i + 2 ] = ( ( float ) ( std::rand( ) % 1000 ) ) * RANDOM_POINT;
  }

  unsigned int VAO, VBO;

  glGenVertexArrays( 1, &VAO );
  glBindVertexArray( VAO );
  glGenBuffers( 1, &VBO );
  glBindBuffer( GL_ARRAY_BUFFER, VBO );
  glBufferData( GL_ARRAY_BUFFER, sizeof( points ), &points, GL_STATIC_DRAW );
  glEnableVertexAttribArray( 0 );
  glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( GL_FLOAT ), 0 );
  glBindVertexArray( 0 );

  return VAO;
}

class ButterfliesUpdaterComponent : public mb::Component
{
  IMPLEMENT_COMPONENT( ButterfliesUpdaterComponent )
public:
  virtual void update( const mb::Clock& clock )
  {
    mb::MaterialComponent* mc = node( )->getComponent<mb::MaterialComponent>( );

    auto mat = mc->first( );

    mat->uniform( "time" )->value( ( float ) clock.getAccumTime( ) );
    mat->uniform( "up" )->value( 0.01f * ( float ) sin( clock.getAccumTime( ) ) );
    mat->uniform( "beta" )->value( ( float ) mb::Mathf::degToRad( -60.0f ) );
  }
};

mb::Program* createProgram( )
{
  mb::Program* program = new mb::Program( );
  program->loadVertexShaderFromText( R"(
    #version 430
    layout (location = 0) in vec3 position;

    uniform float time;
    uniform float up;

    const vec3 vel = vec3( up, 0.1, 0.0 );

    void main()
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

    uniform mat4 mb_MatrixM;
    uniform mat4 mb_MatrixV;
    uniform mat4 mb_MatrixP;

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
      mat4 modelViewProj = mb_MatrixP * mb_MatrixV * mb_MatrixM;
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

mb::Geometry* generateGeom( const mb::Color& )
{
  auto geom = new mb::Geometry( );

  mb::Material* customMaterial = new mb::Material( );
  customMaterial->program = createProgram( );
  customMaterial->addUniform( MB_PROJ_MATRIX,
    std::make_shared< mb::Matrix4Uniform >( ) );
  customMaterial->addUniform( MB_VIEW_MATRIX,
    std::make_shared< mb::Matrix4Uniform >( ) );
  customMaterial->addUniform( MB_MODEL_MATRIX,
    std::make_shared< mb::Matrix4Uniform >( ) );
  customMaterial->addUniform( "time",
    std::make_shared< mb::FloatUniform >( ) );
  customMaterial->addUniform( "up",
    std::make_shared< mb::FloatUniform >( ) );
  customMaterial->addUniform( "beta",
    std::make_shared< mb::FloatUniform >( ) );

  mb::Texture2D* TexDiffuse = mb::Texture2D::loadFromImage( "butterfly.png" );
  customMaterial->addUniform( "image",
    std::make_shared< mb::TextureUniform >( TexDiffuse ) );

  mb::MaterialComponent* mc = geom->getComponent<mb::MaterialComponent>( );
  mc->addMaterial( mb::MaterialPtr( customMaterial ) );

  geom->addComponent( new ButterfliesUpdaterComponent( ) );

  return geom;
}

mb::Group* createScene( void )
{
  vao = createVAO( );
  auto scene = new mb::Group( "scene" );

  auto camera = new mb::Camera( 45.0f, 500 / 500, 0.01f, 1000.0f );
  camera->local( ).translate( 0.0f, 0.0f, 10.0f );

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

  glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );

  mb::Group* _scene = createScene( );

  _scene->perform( mb::UpdateWorldState( ) );

  std::vector< mb::Camera* > _cameras;

  mb::FetchCameras fetchCameras;
  _scene->perform( fetchCameras );
  fetchCameras.forEachCameras( [ &] ( mb::Camera* c )
  {
    if ( mb::Camera::getMainCamera( ) == nullptr || c->isMainCamera( ) )
    {
      mb::Camera::setMainCamera( c );
    }
    _cameras.push_back( c );
  } );

  _scene->perform( mb::StartComponents( ) );

  glEnable( GL_DEPTH_TEST );

  mb::Clock clockTime;
  clockTime.reset( );

  while ( window->isRunning( ) )
  {
    window->pollEvents( );

    if ( mb::Input::isKeyPressed( mb::Keyboard::Key::Esc ) )
    {
      window->close( );
      break;
    }

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    clockTime.tick( );

    _scene->perform( mb::UpdateComponents( clockTime ) );
    _scene->perform( mb::UpdateWorldState( ) );
    std::vector< mb::BatchQueuePtr > bqCollection;

    for ( mb::Camera* c : _cameras )
    {
      if ( c != nullptr && c->isEnabled( ) )
      {
        mb::BatchQueuePtr bq = std::make_shared< mb::BatchQueue >( );
        mb::ComputeBatchQueue cbq( c, bq );
        _scene->perform( cbq );
        bqCollection.push_back( bq );
      }
    };

    if ( !bqCollection.empty( ) )
    {
      mb::BatchQueuePtr mainQueue = nullptr;
      std::for_each( bqCollection.begin( ), bqCollection.end( ), [ &] ( mb::BatchQueuePtr bq )
      {
        if ( bq->getCamera( ) != mb::Camera::getMainCamera( ) )
        {
          std::cout << "OUTSCREEN" << std::endl;
        }
        else
        {
          mainQueue = bq;
        }
      } );

      if ( mainQueue != nullptr )
      {
        auto renderables = mainQueue->renderables( mb::BatchQueue::RenderableType::OPAQUE );
        if ( !renderables.empty( ) )
        {
          for ( mb::Renderable& renderable : renderables )
          {
            //std::cout << "ZDIST: " << renderable.zDistance << std::endl;

            //if ( renderable.zDistance > 128.0f ) continue;

            mb::MaterialComponent* mc = renderable.geometry->getComponent<mb::MaterialComponent>( );

            auto mat = mc->first( );

            mat->uniform( MB_PROJ_MATRIX )->value( mainQueue->getProjectionMatrix( ) );
            mat->uniform( MB_VIEW_MATRIX )->value( mainQueue->getViewMatrix( ) );
            mat->uniform( MB_MODEL_MATRIX )->value( renderable.modelTransform );

            //mat->uniform( MB_VIEWPROJ_MATRIX )->value(
            //  mainQueue->getProjectionMatrix( ) * mainQueue->getViewMatrix( ) );
            mat->use( );



            glBindVertexArray( vao );
            glDrawArrays( GL_POINTS, 0, MAXPOINTS );
            glBindVertexArray( 0 );

            mat->unuse( );
          }
          //std::cout << std::endl << std::endl << " -------------------------- " << std::endl << std::endl;
        }
      }
    }

    window->swapBuffers( );
  }

  delete _scene;

  return 0;
}
