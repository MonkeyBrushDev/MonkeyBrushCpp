#include <iostream>
#include <string>

#include <mb/mb.h>
#include <routes.h>

#include <chrono>

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

class ToggleDepthTest : public mb::Component
{
  IMPLEMENT_COMPONENT( ToggleDepthTest )
public:
  virtual void update( const mb::Clock& ) override
  {
    if ( mb::Input::isKeyPressed( mb::Keyboard::Key::Plus ) )
    {
      std::cout << "ENABLE" << std::endl;
      glEnable( GL_DEPTH_TEST );
    }
    else  if ( mb::Input::isKeyPressed( mb::Keyboard::Key::Minus ) )
    {
      glDisable( GL_DEPTH_TEST );
      std::cout << "DISABLE" << std::endl;
    }
    // std::cout << mb::Input::MouseX( ) << ", " << mb::Input::MouseY( ) << std::endl;
  }
};

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
    _time += _speed * clock.getDeltaTime( );
  }
protected:
  float _speed;
  float _time;
};

mb::Group* createPlanet( float radius, const std::string& diffuse, float equatorialRotationSpeed,
  float orbitSize, float sideralRotationSpeed, const mb::Color& color )
{
  auto geometry = new mb::Geometry( );
  geometry->local( ).setScale( radius );
  geometry->layer( ).set( 0 );


  auto planetRotationPivot = new mb::Group( "" );
  planetRotationPivot->addComponent( new RotationComponent( equatorialRotationSpeed ) );
  planetRotationPivot->addChild( geometry );

  mb::StandardMaterial* customMaterial = new mb::StandardMaterial( );
  customMaterial->setColorMap( mb::Texture2D::loadFromImage( diffuse ) );
  customMaterial->setNormalMap( mb::Texture2D::loadFromImage( "metal-floor-normal.jpg" ) );
  customMaterial->setColor( color );

  mb::MaterialComponent* mc = geometry->getComponent<mb::MaterialComponent>( );
  mc->addMaterial( mb::MaterialPtr( customMaterial ) );

  auto planet = new mb::Group( "name" );
  planet->addChild( planetRotationPivot );
  planet->local( ).setPosition( orbitSize, 0.0f, 0.0f );

  auto planetPivot = new mb::Group( "" );
  planetPivot->addComponent( new RotationComponent( sideralRotationSpeed ) );
  planetPivot->addChild( planet );

  return planetPivot;
}

mb::Group* createScene( void )
{
  std::cout << "NEW BASE DIR2: " << mb::FileSystem::getInstance( )->getBaseDirectory( ) << std::endl;
  vao = createVAO( );
  auto scene = new mb::Group( "scene" );

  auto camera = new mb::Camera( 45.0f, 500 / 500, 0.01f, 1000.0f );
  camera->local( ).translate( 0.0f, 0.0f, 8.0f );



  camera->addComponent( new mb::FreeCameraComponent( ) );
  camera->addComponent( new ToggleDepthTest( ) );
  scene->addChild( camera );

  auto cubes = new mb::Group( "Cubes" );
  mb::Group* g1 = new mb::Group( "MyGroup1" );
  mb::Group* g2 = new mb::Group( "MyGroup2" );

  mb::Texture2D* chesterDiffuse = mb::Texture2D::loadFromImage( "metal-floor.jpg" );
  mb::Texture2D* chesterDNormal = mb::Texture2D::loadFromImage( "metal-floor-normal.jpg" );

  mb::StandardMaterial* customMaterial = new mb::StandardMaterial( );
  customMaterial->setColorMap( chesterDiffuse );
  customMaterial->setNormalMap( chesterDNormal );
  customMaterial->setColor( mb::Color::GREEN );

  mb::StandardMaterial* customMaterial2 = new mb::StandardMaterial( );
  customMaterial2->setColorMap( chesterDiffuse );
  customMaterial2->setNormalMap( chesterDNormal );
  customMaterial2->setColor( mb::Color::GOLD );


  std::vector< mb::Vector3 > cubePositions = {
    mb::Vector3( 2.0f, 5.0f, -15.0f ),
    mb::Vector3( 0.0f, -5.0f, 0.0f ),
    mb::Vector3( -1.5f, -2.2f, -2.5f ),
    mb::Vector3( -3.8f, -2.0f, -12.3f ),
    mb::Vector3( 2.4f, -0.4f, -3.5f ),
    mb::Vector3( -1.7f, 3.0f, -7.5f ),
    mb::Vector3( 1.3f, -2.0f, -2.5f ),
    mb::Vector3( 1.5f, 2.0f, -2.5f ),
    mb::Vector3( 1.5f, 0.2f, -1.5f ),
    mb::Vector3( -1.3f, 1.0f, -1.5f )
  };

  size_t numCubes = cubePositions.size( );
  size_t middleCubes = numCubes / 2;
  for ( unsigned int i = 0; i < middleCubes; ++i )
  {
    auto geom = new mb::Geometry( std::string( "CubeGeom" ) + std::to_string( i + 1 ) );
    geom->local( ).position( ) = cubePositions[ i ];
    geom->local( ).setScale( mb::Vector3( 0.5f ) );

    mb::MaterialComponent* mc = geom->getComponent<mb::MaterialComponent>( );
    mc->addMaterial( mb::MaterialPtr( customMaterial ) );

    geom->addComponent( new RotationComponent( 0.1f ) );
    //geom->addComponent( new mb::RotateComponent( mb::Vector3( -1.0f, -1.0f, 0.0f ), 0.1f ) );
    geom->layer( ).set( i );
    g1->addChild( geom );
  }
  cubes->addChild( g1 );
  for ( unsigned int i = middleCubes; i < numCubes; ++i )
  {
    auto geom = new mb::Geometry( std::string( "CubeGeom" ) + std::to_string( i + 1 ) );
    geom->local( ).setPosition( cubePositions[ i ] );
    geom->local( ).setScale( mb::Vector3( 0.5f ) );

    mb::MaterialComponent* mc = geom->getComponent<mb::MaterialComponent>( );
    mc->addMaterial( mb::MaterialPtr( customMaterial2 ) );

    geom->addComponent( new RotationComponent( 0.1f ) );
    //geom->addComponent( new mb::RotateComponent( mb::Vector3( -1.0f, -1.0f, 0.0f ) * -1.0f, 0.1f ) );
    geom->layer( ).set( i );
    g2->addChild( geom );
  }
  cubes->addChild( g2 );

  scene->addChild( cubes );

  auto earth = createPlanet( 0.5f, "earth.png", 0.05f, 0.5f, 0.1f, mb::Color::BLUE );
  auto moon = createPlanet( 0.15f, "moon.png", 0.025f, 1.15f, 0.035f, mb::Color::BROWN );

  scene->addChild( earth );
  earth->nodeAt<mb::Group>( 0 )->addChild( moon );

  return scene;
}

int main( )
{
  auto start = std::chrono::steady_clock::now( );
  mb::FileSystem::getInstance( )->setBaseDirectory( MB_EXAMPLES_RESOURCES_ROUTE );

  mb::Window* window = new mb::GLFWWindow2( mb::WindowParams( 500, 500 ) );

  auto finish = std::chrono::steady_clock::now( );
  double elapsed_seconds = std::chrono::duration_cast<
    std::chrono::duration<double> >( finish - start ).count( );
  std::cout << elapsed_seconds << std::endl;

  window->init( );

  glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
  auto finish2 = std::chrono::steady_clock::now( );
  double elapsed_seconds2 = std::chrono::duration_cast<
    std::chrono::duration<double> >( finish2 - start ).count( );
  std::cout << elapsed_seconds2 << std::endl;

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
