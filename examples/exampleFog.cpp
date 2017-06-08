#include <iostream>
#include <string>

#include <mb/mb.h>
#include <routes.h>

unsigned int vao;
unsigned int createVAO( )
{
  // Set up vertex data (and buffer(s)) and attribute pointers
  float vertices[ ] = {
    -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
    1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

    -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

    -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    -1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

    1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

    -1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    -1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
    -1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

    -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0, 0.0f, 1.0f,
    1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0, 1.0f, 0.0f,
    1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0, 1.0f, 0.0f,
    -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0, 0.0f, 0.0f,
    -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0, 0.0f, 1.0f
  };
  unsigned int VBO, VAO;
  glGenVertexArrays( 1, &VAO );
  glGenBuffers( 1, &VBO );

  glBindVertexArray( VAO );

  glBindBuffer( GL_ARRAY_BUFFER, VBO );
  glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

  // Position attribute
  glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof( GLfloat ), ( GLvoid* ) 0 );
  glEnableVertexAttribArray( 0 );
  // Normal attribute
  glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof( GLfloat ), ( GLvoid* ) ( 3 * sizeof( GLfloat ) ) );
  glEnableVertexAttribArray( 1 );
  // TexCoord attribute
  glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof( GLfloat ), ( GLvoid* ) ( 6 * sizeof( GLfloat ) ) );
  glEnableVertexAttribArray( 2 );

  glBindVertexArray( 0 ); // Unbind VAO

  return VAO;
}

mb::Program* createProgram( )
{
  mb::Program* program = new mb::Program( );
  program->loadVertexShaderFromText( R"(
    #version 330 core
    layout (location = 0) in vec3 Vertex;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    out vec3 position;

    void main()
    {
      gl_Position = projection * view * model * vec4(Vertex, 1.0);
      position = vec3( view * model * vec4( Vertex, 1.0 ) );
    })" );
  program->loadFragmentShaderFromText( R"(
    #version 330 core
    in vec3 position;
    out vec4 fragColor;

    uniform float density;
    uniform mat4 view;

    const vec3 fogColor = vec3( 0.2 );
    const vec3 color = vec3( 1.0, 0.3, 0.4 );

    void main()
    {
      vec3 viewPos = -transpose(mat3(view)) * view[3].xyz;
      float dst = length(position - viewPos);
      float fogFactor = 1.0 / exp(dst * density);
      fogFactor = clamp(fogFactor, 0.0, 1.0);
      fragColor = vec4(mix(fogColor, color, fogFactor), 1.0);
    })" );
  program->compileAndLink( );
  program->autocatching( );

  return program;
}

mb::Geometry* generateGeom( const mb::Color& c )
{
  auto geom = new mb::Geometry( );

  mb::Material* customMaterial = new mb::Material( );
  customMaterial->program = createProgram( );
  customMaterial->addUniform( "projection",
    std::make_shared< mb::Matrix4Uniform >( ) );
  customMaterial->addUniform( "view",
    std::make_shared< mb::Matrix4Uniform >( ) );
  customMaterial->addUniform( "model",
    std::make_shared< mb::Matrix4Uniform >( ) );
  customMaterial->addUniform( "density",
    std::make_shared< mb::FloatUniform >( 0.04f ) );

  mb::MaterialComponent* mc = geom->getComponent<mb::MaterialComponent>( );
  mc->addMaterial( mb::MaterialPtr( customMaterial ) );

  geom->addComponent( new mb::RotateComponent( mb::Vector3::ONE, 0.25f ) );

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

            mat->uniform( "projection" )->value( mainQueue->getProjectionMatrix( ) );
            mat->uniform( "view" )->value( mainQueue->getViewMatrix( ) );
            mat->uniform( "model" )->value( renderable.modelTransform );
            mat->use( );

            glBindVertexArray( vao );
            glDrawArrays( GL_TRIANGLES, 0, 36 );
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
