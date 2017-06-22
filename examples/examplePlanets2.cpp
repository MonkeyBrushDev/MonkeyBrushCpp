#include <iostream>
#include <string>

#include <routes.h>

#include <mb/mb.h>

#include "../mb/Primitives/SpherePrimitive.hpp"



// geometry render params
unsigned int vao;
mb::SpherePrimitive* sphere;



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

/**
 * @brief The RotationComponent class
 * component to rotate the solar system
 */
class RotationComponent : public mb::Component
{
  IMPLEMENT_COMPONENT( RotationComponent )
public:
  RotationComponent( float speed )
    : _speed( speed )
    , _time( 0.0f )
  { }
  virtual void update( const mb::Clock& clock )
  {
    node( )->local( ).rotate( ).fromAxisAngle(
      mb::Vector3::Y_AXIS, _time * mb::Mathf::TWO_PI );
    _time += _speed *clock.getDeltaTime( );
  }
protected:
  float _speed;
  float _time;
};


class Astro: public mb::Group
{
public:
  mb::Group* tgDis;
  mb::Geometry* geometry;
  mb::SpherePrimitive* sphere;

  mb::Program program;

  Astro( float radius, const std::string& texture, float distance,
    float velRotOrb, float velRot, const mb::Color& )
    : Group( "Astro" )
  {

    program = initProgram( );

    // Setting sphere...
    sphere = new mb::SpherePrimitive( 2, 25, 25);

    GLint inColor=program.attribute("inColor");
    GLint inVertex=program.attribute("inVertex");
    GLint inNormal=program.attribute("inNormal");
    GLint inTexCoord=program.attribute("inTexCoord");

    sphere->bindShaderAttrib(0, inVertex);
    sphere->bindShaderAttrib(1, inColor);
    sphere->bindShaderAttrib(2, inNormal);
    sphere->bindShaderAttrib(3, inTexCoord);
    sphere->setupRender();


    // Link geometry...
    geometry = new mb::Geometry( );
    geometry->local( ).setPosition( mb::Vector3::ZERO );
    geometry->local( ).setScale( radius );

    mb::Texture2D* planetDiffuse = mb::Texture2D::loadFromImage( texture );

    mb::ColorMaterial* customMaterial = new mb::ColorMaterial( );
    customMaterial->setColorMap( planetDiffuse );
    customMaterial->setColor( mb::Color::WHITE );

    mb::MaterialComponent* mc = geometry->getComponent<mb::MaterialComponent>( );
    mc->addMaterial( mb::MaterialPtr( customMaterial ) );

    auto tgRotOrb = new mb::Group( "tgRotOrb" );
    tgDis = new mb::Group( "tgDis" );
    auto tgRot = new mb::Group( "tgRot" );

    tgRot->addChild( geometry );
    tgDis->addChild( tgRot );
    tgRotOrb->addChild( tgDis );
    this->addChild( tgRotOrb );

    tgRotOrb->addComponent( new RotationComponent( velRotOrb * 10.0f ) );
    tgRot->addComponent( new RotationComponent( velRot * 10.0f ) );

    mb::Vector3 pos = this->tgDis->local( ).getPosition( );

    this->tgDis->local( ).setPosition( distance, pos.y(), pos.z() );
  }
  void addSatelite( mb::Group* s )
  {
    this->tgDis->addChild( s );
  }
};

mb::Group* createScene( void )
{
  std::cout << "NEW BASE DIR2: " << mb::FileSystem::getInstance( )->getBaseDirectory( ) << std::endl;

  //vao = createVAO( );

  auto scene = new mb::Group( "scene" );

  auto camera = new mb::Camera( 45.0f, 500 / 500, 0.01f, 1000.0f );
  camera->local( ).translate( 0.0f, 0.0f, 20.0f );

  auto sun = new Astro( 6.0f / 2.0f, "sun.png", 0.0f, 0.0f, 0.002f, mb::Color::YELLOW );
  auto earth = new Astro( 1.27f / 2.0f, "earth.png", 6.0f, 0.001f, 0.005f, mb::Color::BLUE );
  auto moon = new Astro( 0.34f / 2.0f, "moon.png", 1.0f, 0.01f, 0.0f, mb::Color::WHITE );

  scene->addChild( sun );
  sun->addSatelite( earth );
  earth->addSatelite( moon );

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

  // Cameras setting...
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
  // --

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

  mb::Texture2D* tex = new mb::Texture2D( 50, 50 );
  tex->loadFromImage("../resources/texture.jpg");
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

    clockTime.tick( );

    _scene->perform( mb::UpdateComponents( clockTime ) );

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
        if (bq->getCamera() != mb::Camera::getMainCamera())
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
            tex->bind( 0 );
            glUniform1i( texLoc, 0 );

            program.sendUniform4m( "projection", mainQueue->getProjectionMatrix().values().data() );
            program.sendUniform4m( "view", mainQueue->getViewMatrix().values().data());
            program.sendUniform4m( "model", renderable.modelTransform.data());
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
