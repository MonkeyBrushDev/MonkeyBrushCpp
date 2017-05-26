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

#include "App.hpp"
#include "OpenGL/OpenGLRenderer.hpp"
#include "Rendering/Renderer.hpp"

#include "Visitors/StartComponents.hpp"
#include "Visitors/FetchCameras.hpp"
#include "Visitors/ComputeBatchQueue.hpp"
#include "Visitors/UpdateWorldState.hpp"

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
    // TODO: Fixed update _scene->perform( UpdateComponents( dt ) );

    _scene->perform( UpdateWorldState( ) );

    std::vector< BatchQueuePtr > bqCollection;

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
    std::cout << "~~~~~~~~~~~ END UPDATE ~~~~~~~~~~~" << std::endl;

    // RENDER STEP
    // TODO
    std::cout << "~~~~~~~~~~ BEGIN RENDER ~~~~~~~~~~" << std::endl;
    _renderer->beginRender( );
    _renderer->clearBuffers( );
    std::cout << "~~~~~~~~~~ RENDER SCENE ~~~~~~~~~~" << std::endl;
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
          _renderer->render( bq, bq->camera( )->renderPass( ) );
        }
        else
        {
          mainQueue = bq;
        }
      } );

      if ( mainQueue != nullptr ) // TODO: CORRECT COMPARISON??
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
