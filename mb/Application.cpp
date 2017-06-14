#include "Application.hpp"

#include "Visitors/StartComponents.hpp"
#include "Visitors/FetchCameras.hpp"
#include "Visitors/ComputeBatchQueue.hpp"
#include "Visitors/UpdateWorldState.hpp"

namespace mb
{
  Application::Application( void )
  {

  }
  ~Application::Application( void )
  {

  }
  void Application::setSceneNode( Group/*Scene*/* node )
  {
    _scene = node;
    _cameras.clear( );

    if ( _scene != nullptr )
    {
      _scene->perform( UpdateWorldState( ) ); // Update state matrix for all scenegraph

      FetchCameras fetchCameras;
      _scene->perform( fetchCameras );
      fetchCameras.forEachCamera( [ &] ( Camera* c )
      {
        if ( Camera::getMainCamera( ) == nullptr || c->isMainCamera( ) )
        {
          Camera::setMainCamera( c );
        }
        _cameras.push_back( c );
      } );

      _scene->perform( StartComponents( ) );

      _simulationClock.reset( );
    }
  }
  int Application::run( void )
  {
    bool fail = false;
    while ( !fail )
    {
      fail = !update( );
    }
    return 0;
  }
  bool Application::update( void )
  {
    // UPDATE STEP
    clockTime.tick( );
    _scene->perform( mb::UpdateComponents( clockTime ) );
    _scene->perform( mb::UpdateWorldState( ) );

    std::vector< BatchQueuePtr > bqCollection;

    std::vector< mb::Light* > lights;
    mb::FetchLights fl;
    _scene->perform( fl );
    lights = fl.lights( );

    forEachCamera( [ &] ( Camera *c )
    {
      if ( c != nullptr && c->isEnabled( ) )
      {
        BatchQueuePtr bq = std::make_shared<BatchQueue>( );
        ComputeBatchQueue cbq( c, bq );
        _scene->perform( cbq );
        bqCollection.push_back( bq );
      }
    } );
    // \\ UPDATE STEP

    // RENDER STEP
    //_renderer->beginRender( );
    //_renderer->clearBuffers( );
    if ( !bqCollection.empty( ) )
    {
      BatchQueuePtr mainQueue = nullptr;
      std::for_each( bqCollection.begin( ),
        bqCollection.end( ), [ &] ( BatchQueuePtr bq )
      {
        if ( bq->camera( ) != Camera::getMainCamera( ) )
        {
          // Render queue with bq camera
          std::cout << "Render outscreen (" << bq->camera( )->name( ) << ")" << std::endl;
          //_renderer->render( bq, bq->camera( )->renderPass( ) );
        }
        else
        {
          mainQueue = bq;
        }
      } );

      if ( mainQueue != nullptr )
      {
        // Render main queue
        std::cout << "render main queue (" << mainQueue->camera( )->name( ) << ")" << std::endl;
        //_renderer->render( mainQueue, mainQueue->camera( )->renderPass( ) );
      }
    }
    //_renderer->endRender( );
    // \\ RENDER STEP
    return false;
  }
}

#endif /* __MB_APPLICATION__ */
