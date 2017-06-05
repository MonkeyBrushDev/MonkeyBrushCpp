#include <iostream>
#include <string>

#include <routes.h>

#include <mb/mb.h>

#include "../mb/Primitives/SpherePrimitive.hpp"
#include "../mb/Primitives/TorusPrimitive.hpp"


mb::Program initProgram( )
{
  mb::Program program;
  program.loadVertexShaderFromText(R"(
    #version 330 core
    in vec3 inVertex;
    in vec3 inColor;
    in vec3 inNormal;
    in vec2 inTexCoord;

    out vec3 vcolor;
    out vec3 vnormal;
    out vec2 vtexCoord;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    void main()
    {
      vcolor = inColor;
      vnormal = inNormal;
      vtexCoord = vec2( inTexCoord.x, 1.0 - inTexCoord.y);

      gl_Position = projection * view * model * vec4( inVertex.xyz, 1.0f);
    })");
  program.loadFragmentShaderFromText(R"(
    #version 330 core
    in vec3 vcolor;
    in vec3 vnormal;
    in vec2 vtexCoord;

    const vec3 lightColor = vec3(0.0, 1.0, 1.0);
    const vec3 lightPos = vec3(1.0, 1.0, 1.0);

    uniform sampler2D myTexture;

    out vec4 outColor;

    void main()
    {
      float cosTheta = dot(vnormal, lightPos);

      outColor = vec4( (lightColor*cosTheta)+vcolor, 0.5f );
      //outColor = outColor + texture( myTexture, vtexCoord );

      //outColor = vec4( vtexCoord, 0.0, 1.0 );
      //outColor = texture( myTexture, vtexCoord );

    })");
  program.compileAndLink( );
  program.autocatching();

  return program;
}




int main( )
{

  // -----      Scene init       ----- //

  mb::FileSystem::getInstance()->setBaseDirectory( MB_EXAMPLES_RESOURCES_ROUTE );

  mb::Window* window = new mb::GLFWWindow2( mb::WindowParams( 500, 500 ) );
  window->init( );

  // Setting shaders...

  mb::Program program = initProgram( );

//  program.addUniform( "projection" );
//  program.addUniform( "view" );
//  program.addUniform( "model" );
  GLint inColor=program.attribute("inColor");
  GLint inVertex=program.attribute("inVertex");
  GLint inNormal=program.attribute("inNormal");
  GLint inTexCoord=program.attribute("inTexCoord");

  // Creating sphere mesh...
  mb::SpherePrimitive* sphere = new mb::SpherePrimitive( 2, 25, 25);
  //mb::TorusPrimitive* sphere = new mb::TorusPrimitive();

  sphere->bindShaderAttrib(0, inVertex);
  sphere->bindShaderAttrib(1, inColor);
  sphere->bindShaderAttrib(2, inNormal);
  sphere->bindShaderAttrib(3, inTexCoord);
  sphere->setupRender();

  unsigned int vao = sphere->getVAO();


  // Creating scene ...

  auto scene = new mb::Group( "scene" );
  auto camera = new mb::Camera( 45.0f, 500/500, 0.01f, 1000.0f );
  camera->local( ).translate( 0.0f, 0.0f, -8.0f );

  scene->addChild( camera );
  scene->addChild(new mb::Geometry());

  //---------

  mb::Texture2D* tex = new mb::Texture2D( "../resources/texture.jpg" );
  int texLoc = glGetUniformLocation( program.program( ), "myTexture");

  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

  mb::Group* _scene = scene;

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
        if (bq->camera() != mb::Camera::getMainCamera())
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
          for ( mb::Renderable*& renderable : renderables )
          {
            tex->bind( 0 );
            glUniform1i( texLoc, 0 );

            program.sendUniform4m( "projection", mainQueue->getProjectionMatrix().values().data() );
            program.sendUniform4m( "view", mainQueue->getViewMatrix().values().data());
            program.sendUniform4m( "model", renderable->geom->world().
                                   computeModel().values( ).data( ));
            program.use();

            sphere->render();

            program.unuse();
          }
        }
      }
    }


    window->swapBuffers( );
  }
  return 0;
}
