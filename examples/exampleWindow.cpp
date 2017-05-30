#include <iostream>
#include <string>

#include <mb/mb.h>

unsigned int createVAO( )
{
  // Set up vertex data (and buffer(s)) and attribute pointers
  float vertices[] = {
    -1.0f, -1.0f, -1.0f,  0.0f, 0.0f,
     1.0f, -1.0f, -1.0f,  1.0f, 0.0f,
     1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
     1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
    -1.0f,  1.0f, -1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,  0.0f, 0.0f,

    -1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
     1.0f, -1.0f,  1.0f,  1.0f, 0.0f,
     1.0f,  1.0f,  1.0f,  1.0f, 1.0f,
     1.0f,  1.0f,  1.0f,  1.0f, 1.0f,
    -1.0f,  1.0f,  1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  1.0f,  0.0f, 0.0f,

    -1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
    -1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
    -1.0f,  1.0f,  1.0f,  1.0f, 0.0f,

     1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
     1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
     1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
     1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
     1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
     1.0f,  1.0f,  1.0f,  1.0f, 0.0f,

    -1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
     1.0f, -1.0f, -1.0f,  1.0f, 1.0f,
     1.0f, -1.0f,  1.0f,  1.0f, 0.0f,
     1.0f, -1.0f,  1.0f,  1.0f, 0.0f,
    -1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
    -1.0f, -1.0f, -1.0f,  0.0f, 1.0f,

    -1.0f,  1.0f, -1.0f,  0.0f, 1.0f,
     1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
     1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
     1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
    -1.0f,  1.0f,  1.0f,  0.0f, 0.0f,
    -1.0f,  1.0f, -1.0f,  0.0f, 1.0f
  };
  unsigned int VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  // TexCoord attribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(2);

  glBindVertexArray(0); // Unbind VAO

  return VAO;
}

mb::Program initProgram( )
{
  mb::Program program;
  program.loadVertexShaderFromText(R"(
    #version 330 core
    layout (location = 0) in vec3 position;
    layout (location = 2) in vec2 texCoord;

    out vec2 TexCoord;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    void main()
    {
      gl_Position = projection * view * model * vec4(position, 1.0f);
      TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);
    })");
  program.loadFragmentShaderFromText(R"(
    #version 330 core
    in vec2 TexCoord;

    out vec4 color;

    uniform sampler2D myTexture;

    void main()
    {
      color = vec4( TexCoord, 0.0, 1.0 );
      color = texture( myTexture, TexCoord );
    })");
  program.compileAndLink( );
  program.autocatching();

  return program;
}

class ToggleDepthTest : public mb::Component
{
  IMPLEMENT_COMPONENT( ToggleDepthTest )
public:
  virtual void update( const float& ) override
  {
    if ( mb::Input::isKeyPressed( mb::Keyboard::Key::Plus ) )
    {
      std::cout << "ENABLE" << std::endl;
      glEnable(GL_DEPTH_TEST);
    } else  if ( mb::Input::isKeyPressed( mb::Keyboard::Key::Minus ) )
    {
      glDisable(GL_DEPTH_TEST);
      std::cout << "DISABLE" << std::endl;
    }
    // std::cout << mb::Input::MouseX( ) << ", " << mb::Input::MouseY( ) << std::endl;
  }
};

#include <routes.h>

int main( )
{
  mb::FileSystem::getInstance()->setBaseDirectory( MB_EXAMPLES_RESOURCES_ROUTE );

  mb::Window* window = new mb::GLFWWindow2( mb::WindowParams( 500, 500 ) );
  window->init( );

  mb::Material customMaterial;

  mb::Program program = initProgram( );
  unsigned int vao = createVAO( );

  customMaterial.program = program;
  customMaterial.addUniform("projection",
        std::make_shared< mb::Uniform >( mb::UniformType::Matrix4 ) );
  customMaterial.addUniform("view",
        std::make_shared< mb::Uniform >( mb::UniformType::Matrix4 ) );
  /*customMaterial.addUniform("model",
        std::make_shared< mb::Uniform >( mb::UniformType::Matrix4 ) );*/

  auto scene = new mb::Group( "scene" );
  auto camera = new mb::Camera( 45.0f, 500/500, 0.01f, 1000.0f );
  camera->local( ).translate( 0.0f, 0.0f, -8.0f );

  camera->addComponent( new mb::FreeCameraComponent( ) );
  camera->addComponent( new ToggleDepthTest( ) );

  scene->addChild( camera );

  auto cubes = new mb::Group( "Cubes" );
  mb::Group* g1 = new mb::Group("MyGroup1");
  mb::Group* g2 = new mb::Group("MyGroup2");

  mb::Vector3 cubePositions[] = {
    mb::Vector3(  2.0f,  5.0f, -15.0f ),
    mb::Vector3(  0.0f,  0.0f,   0.0f ),
    mb::Vector3( -1.5f, -2.2f,  -2.5f ),
    mb::Vector3( -3.8f, -2.0f, -12.3f ),
    mb::Vector3(  2.4f, -0.4f,  -3.5f ),
    mb::Vector3( -1.7f,  3.0f,  -7.5f ),
    mb::Vector3(  1.3f, -2.0f,  -2.5f ),
    mb::Vector3(  1.5f,  2.0f,  -2.5f ),
    mb::Vector3(  1.5f,  0.2f,  -1.5f ),
    mb::Vector3( -1.3f,  1.0f,  -1.5f )
  };

  for ( unsigned int i = 0; i < 5; ++i )
  {
    auto geom = new mb::Geometry( std::string( "CubeGeom" ) + std::to_string( i + 1 ) );
    geom->local( ).setPosition( cubePositions[ i ] );
    geom->local( ).setScale( mb::Vector3( 0.5f ) );

    geom->addComponent( new mb::RotateComponent( mb::Vector3( -1.0f, -1.0f,  0.0f ), 0.1f ) );

    geom->layer( ).set( i );

    g1->addChild( geom );
  }
  cubes->addChild( g1 );
  for ( unsigned int i = 5; i < 10; ++i )
  {
    auto geom = new mb::Geometry( std::string( "CubeGeom" ) + std::to_string( i + 1 ) );
    geom->local( ).setPosition( cubePositions[ i ] );
    geom->local( ).setScale( mb::Vector3( 0.5f ) );

    //geom->addComponent( new mb::RotateComponent( mb::Vector3( -1.0f, -1.0f,  0.0f ), 0.1f ) );

    geom->layer( ).set( i );

    g2->addChild( geom );
  }
  cubes->addChild( g2 );

  scene->addChild( cubes );

  mb::Texture2D* tex = new mb::Texture2D( "texture.jpg" );
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

  mb::Group* _scene = scene;

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

  float dt = 0.0f;
  float lastFrame = 0.0f;


  //int projLoc = glGetUniformLocation(program.program( ), "projection");
  //int viewLoc = glGetUniformLocation(program.program( ), "view");
  int texLoc = glGetUniformLocation(program.program( ), "myTexture");


  glEnable( GL_DEPTH_TEST );

  mb::Clock clockTime;
  clockTime.reset( );

  while( window->isRunning( ) )
  {
    window->pollEvents( );

    if (mb::Input::isKeyPressed(mb::Keyboard::Key::Esc))
    {
      window->close( );
      break;
    }

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    float currentFrame = glfwGetTime();
    dt = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // TODO: float dt2 = clockTime.deltaTime( );
    // TODO: clockTime.tick( );

    // TODO: std::cout << "DT1: " << dt << " - DT2: " << dt2 << std::endl;

    _scene->perform( mb::UpdateComponents( dt ) );

    _scene->perform( mb::UpdateWorldState( ) );

    std::vector< mb::BatchQueuePtr > bqCollection;

    for( mb::Camera* c: _cameras)
    {
      if ( c != nullptr && c->isEnabled( ) )
      {
        mb::BatchQueuePtr bq = std::make_shared< mb::BatchQueue >( );
        mb::ComputeBatchQueue cbq( c, bq );
        _scene->perform( cbq );
        bqCollection.push_back( bq );
      }
    };

    if (!bqCollection.empty())
    {
      mb::BatchQueuePtr mainQueue = nullptr;
      std::for_each( bqCollection.begin(), bqCollection.end(), [&](mb::BatchQueuePtr bq)
      {
        if (bq->getCamera( ) != mb::Camera::getMainCamera( ))
        {
          std::cout << "OUTSCREEN" << std::endl;
        }
        else
        {
          mainQueue = bq;
        }
      });

      if(mainQueue.get() != nullptr)
      {
        auto renderables = mainQueue->renderables( mb::BatchQueue::RenderableType::OPAQUE );
        if ( !renderables.empty( ) )
        {
          for ( mb::Renderable& renderable : renderables )
          {
            //program.use();
            //glUniformMatrix4fv(projLoc, 1, GL_FALSE, mainQueue->getProjectionMatrix().values( ).data( ) );
            //glUniformMatrix4fv(viewLoc, 1, GL_FALSE, mainQueue->getViewMatrix().values( ).data( ) );

            //std::cout << "ZDIST: " << renderable->zDistance << std::endl;

            customMaterial.uniform("projection")->value(mainQueue->getProjectionMatrix());
            customMaterial.uniform("view")->value(mainQueue->getViewMatrix());
            customMaterial.use( );


            tex->bind( 0 );
            glUniform1i(texLoc, 0);

            glBindVertexArray(vao);
            customMaterial.program.sendUniform4m( "model", renderable.modelTransform.values( ).data( ));
            glDrawArrays(GL_TRIANGLES, 0, 36);
            glBindVertexArray(0);
            //program.unuse();

            customMaterial.unuse( );
          }

          /*std::cout << " ---------------- " << std::endl;
          std::cout << " ---------------- " << std::endl;
          std::cout << " ---------------- " << std::endl;*/
        }
      }
    }


    window->swapBuffers( );
  }
  return 0;
}
