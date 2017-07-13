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

mb::Program* createProgram( )
{
  mb::Program* program = new mb::Program( );
  program->loadVertexShaderFromText( R"(
    #version 330 core
    layout (location = 0) in vec3 position;
    layout (location = 1) in vec3 normal;
    layout (location = 2) in vec2 texCoord;

    uniform mat4 MB_MATRIXM;
    uniform mat4 MB_MATRIXV;
    uniform mat4 MB_MATRIXP;

    out vec3 outPosition;
    out vec3 Normal;
    out vec2 TexCoord;

    void main()
    {
      gl_Position = MB_MATRIXP * MB_MATRIXV * MB_MATRIXM * vec4(position, 1.0);
      mat3 normalMatrix = mat3(transpose(inverse( MB_MATRIXM )));
      Normal = normalMatrix * normal;
      outPosition = vec3( MB_MATRIXM * vec4( position, 1.0 ) );
      TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);
    })" );
  program->loadFragmentShaderFromText( R"(
    #version 330 core
    out vec4 fragColor;

    in vec3 outPosition;
    in vec3 Normal;
    in vec2 TexCoord;

    uniform mat4 MB_MATRIXV;

    struct SurfaceOutput
    {
      vec3 Albedo;
      vec3 Normal;
      vec3 Emissiton;
      float Specular;
      float Gloss;
      float Alpha;
    };

    vec4 LightingPhong( in SurfaceOutput s, in vec3 __LightPosition, in vec3 __LightColor )
    {
      vec3 viewPos = -transpose(mat3(MB_MATRIXV)) * MB_MATRIXV[3].xyz;

      vec3 lightDir = normalize(__LightPosition - outPosition);

      // Ambient
      vec3 ambient = vec3(0.4);

      // Diffuse
      float diff = max( dot( s.Normal, lightDir ), 0.0 );
      vec3 diffuse = diff * __LightColor;

      // Specular
      vec3 viewDir = normalize( viewPos - outPosition );
      vec3 h = normalize( lightDir + viewDir );

      vec3 reflectDir = reflect(-lightDir, s.Normal);
      float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8.0);
      vec3 specular = vec3(0.3) * spec;

      return vec4(
        ( ambient + diffuse + specular ) * s.Albedo,
        1.0
      );
    }

    vec4 LightingBlinnPhong( in SurfaceOutput s, in vec3 __LightPosition, in vec3 __LightColor )
    {
      vec3 viewPos = -transpose(mat3(MB_MATRIXV)) * MB_MATRIXV[3].xyz;

      vec3 lightDir = normalize(__LightPosition - outPosition);

      // Ambient
      vec3 ambient = vec3(0.4);

      // Diffuse
      float diff = max( dot( s.Normal, lightDir ), 0.0 );
      vec3 diffuse = diff * __LightColor;

      // Specular
      vec3 viewDir = normalize( viewPos - outPosition );
      vec3 h = normalize( lightDir + viewDir );
      float spec = pow(max(dot(s.Normal, h), 0.0), 32.0);
      vec3 specular = vec3(0.3) * spec;

      return vec4(
        ( ambient + diffuse + specular ) * s.Albedo,
        1.0
      );
    }

    vec4 LightingLambert( in SurfaceOutput s, in vec3 __LightPosition, in vec3 __LightColor )
    {
      vec3 viewPos = -transpose(mat3(MB_MATRIXV)) * MB_MATRIXV[3].xyz;

      vec3 lightDir = normalize(__LightPosition - outPosition);

      // Ambient
      vec3 ambient = vec3(0.4);

      // Diffuse
      float diff = max( dot( s.Normal, lightDir ), 0.0 );
      vec3 diffuse = diff * __LightColor;

      return vec4(
        ( ambient + diffuse ) * s.Albedo,
        1.0
      );
    }

    #define MODE Lambert

    vec4 LightingSimple( in SurfaceOutput s, in vec3 __LightPosition, in vec3 __LightColor )
    {
      return vec4(
        s.Albedo,
        1.0
      );
    }

    void shader_frag( out SurfaceOutput s );


    #define JOIN_(X,Y) X##Y
    #define JOIN(X,Y) JOIN_(X,Y)
    #ifndef MODE
      #define MODE Phong
    #endif
    #define LIGHT_MODE JOIN(Lighting, MODE)

    void main( )
    {
      SurfaceOutput s;
      shader_frag( s );

      fragColor = vec4( 0.0, 0.0, 0.0, 1.0 );
      fragColor.rgb += LIGHT_MODE ( s, vec3( 0.7, 0.2, 2.0 ), vec3( 0.2, 0.2, 0.6 ) ).rgb;
      fragColor.rgb += LIGHT_MODE ( s, vec3( 2.3, -3.3, -4.0 ), vec3( 0.3, 0.3, 0.7 ) ).rgb;
      fragColor.rgb += LIGHT_MODE ( s, vec3( -4.0, 2.0, -12.0 ), vec3( 0.0, 0.0, 0.3 ) ).rgb;
      fragColor.rgb += LIGHT_MODE ( s, vec3( 0.0, 0.0, -3.0 ), vec3( 0.4, 0.4, 0.4 ) ).rgb;
    }

    const vec3 color = vec3( 0.2, 0.2, 0.5 );

    void shader_frag( out SurfaceOutput s )
    {
      s.Albedo = color;
      s.Normal = Normal;
    }
)" );
  program->compileAndLink( );
  program->autocatching( );

  return program;
}

mb::Geometry* generateGeomWithLight( const mb::Color& )
{
  auto geom = new mb::Geometry( );
  geom->addPrimitive( new mb::SpherePrimitive( 0.75f, 15, 15 ) );

  mb::Material* customMaterial = new mb::Material( );
  customMaterial->program = createProgram( );
  customMaterial->addUniform( MB_PROJ_MATRIX,
    std::make_shared< mb::Matrix4Uniform >( ) );
  customMaterial->addUniform( MB_VIEW_MATRIX,
    std::make_shared< mb::Matrix4Uniform >( ) );
  customMaterial->addUniform( MB_MODEL_MATRIX,
    std::make_shared< mb::Matrix4Uniform >( ) );

  mb::MaterialComponent* mc = geom->getComponent<mb::MaterialComponent>( );
  mc->addMaterial( mb::MaterialPtr( customMaterial ) );

  return geom;
}

mb::Geometry* generateGeom( const mb::Color& c )
{
  auto geom = new mb::Geometry( );
  geom->addPrimitive( new mb::CubePrimitive( 1.0f ) );

  mb::BasicMaterial* customMaterial = new mb::BasicMaterial( );
  customMaterial->setColor( c );

  mb::MaterialComponent* mc = geom->getComponent<mb::MaterialComponent>( );
  mc->addMaterial( mb::MaterialPtr( customMaterial ) );

  //geom->addComponent( new mb::RotateComponent( mb::Vector3::ONE, 0.15f ) );

  return geom;
}

mb::Group* createScene( void )
{
  auto scene = new mb::Group( "scene" );

  auto camera = new mb::Camera( 60.0f, 800 / 600, 0.01f, 1000.0f );
  camera->local( ).translate( 0.0f, 0.0f, 10.0f );
  camera->addComponent( new mb::FreeCameraComponent( ) );
  scene->addChild( camera );


  std::vector< mb::Vector3 > cubePositions = {
    mb::Vector3( 0.0f,  0.0f,  0.0f),
    mb::Vector3( 2.0f,  5.0f, -15.0f),
    mb::Vector3(-1.5f, -2.2f, -2.5f),
    mb::Vector3(-3.8f, -2.0f, -12.3f),
    mb::Vector3( 2.4f, -0.4f, -3.5f),
    mb::Vector3(-1.7f,  3.0f, -7.5f),
    mb::Vector3( 1.3f, -2.0f, -2.5f),
    mb::Vector3( 1.5f,  2.0f, -2.5f),
    mb::Vector3( 1.5f,  0.2f, -1.5f),
    mb::Vector3(-1.3f,  1.0f, -1.5f)
  };

  for ( unsigned int i = 0; i < cubePositions.size( ); ++i)
  {
    auto node = generateGeomWithLight( mb::Color::GREY );
    node->local().setPosition(cubePositions[i]);
    scene->addChild( node );
  }

  std::vector< mb::Vector3 > pointLightPositions = {
    mb::Vector3( 0.7f,  0.2f,  2.0f),
    mb::Vector3( 2.3f, -3.3f, -4.0f),
    mb::Vector3(-4.0f,  2.0f, -12.0f),
    mb::Vector3( 0.0f,  0.0f, -3.0f)
  };
  std::vector< mb::Vector3 > pointLightColor = {
    mb::Vector3( 0.2f,  0.2f,  0.6f),
    mb::Vector3( 0.3f, 0.3f, 0.7f),
    mb::Vector3( 0.0f,  0.0f, 0.3f),
    mb::Vector3( 0.4f,  0.4f, .4f)
  };

  for ( unsigned int i = 0; i < pointLightColor.size( ); ++i )
  {
    mb::Color cc(pointLightColor[i].x(), pointLightColor[i].y(),pointLightColor[i].z( ));
    mb::Group* lg = new mb::Group( "" );
    mb::Light* l = new mb::Light( );
    l->local( ).setPosition( pointLightPositions[i] );
    l->setColor( cc );
    auto nl = generateGeom( cc );
    nl->local( ).setPosition( pointLightPositions[i] );
    lg->addChild( l );
    lg->addChild( nl );

    scene->addChild( lg );
    nl->local( ).setScale( 0.25f );
  }

  return scene;
}

int main( )
{
  mb::FileSystem::getInstance( )->setBaseDirectory( MB_EXAMPLES_RESOURCES_ROUTE );

  mb::Window* window = new mb::GLFWWindow2( mb::WindowParams( 800, 600 ) );
  window->init( );

  glClearColor( 0.1f, 0.1f, 0.1f, 1.0f );

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

    std::vector< mb::Light* > lights;
    mb::FetchLights fl;
    _scene->perform( fl );
    lights = fl.lights( );

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

            renderable.geometry->forEachPrimitive( [] ( mb::Primitive* p )
            {
              p->render( );
            } );

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
