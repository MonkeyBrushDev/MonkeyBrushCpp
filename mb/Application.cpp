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

#include "Application.hpp"

#include "Visitors/StartComponents.hpp"
#include "Visitors/FetchCameras.hpp"
#include "Visitors/FetchLights.hpp"
#include "Visitors/ComputeBatchQueue.hpp"
#include "Visitors/UpdateComponents.hpp"
#include "Visitors/UpdateWorldState.hpp"
#include "Visitors/DebugRenderVisitor.hpp"

#include "OpenGL/OpenGLRenderer.hpp"

namespace mb
{
  Application::Application( void )
  {
    _renderer = new OpenGLRenderer( );
  }
  Application::~Application( void )
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
      fetchCameras.forEachCameras( [ &] ( Camera* c )
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
    _simulationClock.tick( );
    _scene->perform( mb::UpdateComponents( _simulationClock ) );
    _scene->perform( mb::UpdateWorldState( ) );

    std::vector< BatchQueuePtr > bqCollection;

    std::vector< mb::Light* > lights;
    mb::FetchLights fl;
    _scene->perform( fl );
    lights = fl.lights( );

    for ( auto c : _cameras )
    {
      if ( c != nullptr && c->isEnabled( ) )
      {
        BatchQueuePtr bq = std::make_shared<BatchQueue>( );
        ComputeBatchQueue cbq( c, bq );
        _scene->perform( cbq );
        bqCollection.push_back( bq );
      }
    }
    // \\ UPDATE STEP

    // RENDER STEP
    _renderer->beginRender( );

    // CLEAR COLOR (MODE TO ANOTHER ZONE) NOT BEST OPTION (ONLY MAIN CAMERA??)
    auto clearColor = Camera::getMainCamera( )->getClearColor( );
    glClearColor( clearColor.r(), clearColor.g(), clearColor.b(), clearColor.a() );

    _renderer->clearBuffers( );
    if ( !bqCollection.empty( ) )
    {
      BatchQueuePtr mainQueue = nullptr;
      std::for_each( bqCollection.begin( ),
        bqCollection.end( ), [ &] ( BatchQueuePtr bq )
      {
        if ( bq->getCamera( ) != Camera::getMainCamera( ) )
        {
          _renderer->render( bq, bq->getCamera( )->renderPass( ) );
        }
        else
        {
          mainQueue = bq;
        }
      } );

      if ( mainQueue != nullptr )
      {
        _renderer->render( mainQueue, mainQueue->getCamera( )->renderPass( ) );
      }
    }
    _renderer->endRender( );

    if( debug )
    {
      _scene->perform( mb::DebugRenderVisitor(
        _renderer, mb::Camera::getMainCamera( ) ) );
    }
    // \\ RENDER STEP
    return false;
  }
}
