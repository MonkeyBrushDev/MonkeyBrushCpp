#include "App.hpp"
#include "Rendering/Renderer.hpp"

#include "visitors/StartComponents.hpp"
#include "visitors/FetchCameras.hpp"
#include "visitors/FetchGeometry.hpp"
#include "visitors/UpdateWorldState.hpp"

namespace mb
{
  App::App( void )
  {
    //addSystem( new UpdateSystem( ) );
    //addSystem( new RenderSystem( ) );
    _renderer = new OpenGLRenderer( );
  }
  App::~App( void )
  {
  }

  void App::setSceneNode( Scene* n )
  {
    _scene = n;
    _cameras.clear( );

    if ( _scene != nullptr )
    {
      FetchCameras fetchCameras;
      _scene->perform( fetchCameras );
      fetchCameras.forEachCamera( [ &] ( Camera* c )
      {
        if ( Camera::mainCamera( ) == nullptr || c->isMainCamera( ) )
        {
          Camera::mainCamera( c );
        }
        _cameras.push_back( c );
      } );

      _scene->perform( StartComponents( ) );

      _simulationClock.reset( );
    }
  }

  void App::start( void )
  {
    startSystems( );
  }

  int App::run( void )
  {
    start( );
    bool fail = false;
    while ( !fail )
    {
      fail = !update( );
    }
    return 0;
  }

  bool App::update( void )
  {
    std::cout << "Engine will update" << std::endl;
    std::cout << "~~~~~~~~~~ BEGIN UPDATE ~~~~~~~~~~" << std::endl;
    // UPDATE STEP
    // TODO: Fixed update
    _scene->perform( UpdateWorldState( ) );

    std::vector<BatchQueue*> rqCollection;

    forEachCamera( [ &] ( Camera *c )
    {
      if ( c != nullptr )
      {
        BatchQueue* rq = new BatchQueue( );
        FetchGeometry fg( c, rq );
        _scene->perform( fg );
        rqCollection.push_back( rq );
      }
    } );
    // \\ UPDATE STEP
    std::cout << "~~~~~~~~~~~ END UPDATE ~~~~~~~~~~~" << std::endl;

    // RENDER STEP
    // TODO
    std::cout << "~~~~~~~~~~ BEGIN RENDER ~~~~~~~~~~" << std::endl;
    _renderer->beginRender( );
    _renderer->clearBuffers( );
    std::cout << "~~~~~~~~~~ RENDER SCENE ~~~~~~~~~~" << std::endl;
    if ( !rqCollection.empty( ) )
    {
      BatchQueue *mainQueue = nullptr;
      std::for_each( rqCollection.begin( ),
        rqCollection.end( ), [ &] ( BatchQueue* rq )
      {
        if ( rq->camera( ) != Camera::mainCamera( ) )
        {
          // Render queue with rq camera
          std::cout << "Render outscreen (" << rq->camera( )->name( ) << ")" << std::endl;
          _renderer->render( rq, rq->camera( )->renderPass( ) );
        }
        else
        {
          mainQueue = rq;
        }
      } );

      if ( mainQueue != nullptr )
      {
        // Render main queue
        std::cout << "render main queue (" << mainQueue->camera( )->name( ) << ")" << std::endl;
        _renderer->render( mainQueue, mainQueue->camera( )->renderPass( ) );
      }
    }
    std::cout << "~~~~~~~~~~~ END RENDER ~~~~~~~~~~~" << std::endl;
    _renderer->endRender( );
    // \\ RENDER STEP
    std::cout << "Engine did update" << std::endl;

    return false;
  }

  void App::stop( void )
  {
    setSceneNode( nullptr );
  }
}
