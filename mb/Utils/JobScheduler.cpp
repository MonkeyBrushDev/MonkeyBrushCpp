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

#include "JobScheduler.hpp"

namespace mb
{
  namespace concurrency
  {
    std::size_t JobQueue::size( void )
    {
      Lock lock( _mutex );
      return _jobs.size( );
    }
    bool JobQueue::empty( void ) const
    {
      return _jobs.empty( );
    }
    void JobQueue::push( const Job::JobPtr& job )
    {
      Lock lock( _mutex );
      _jobs.push_back( job );
    }
    Job::JobPtr JobQueue::pop( void )
    {
      Lock lock( _mutex );
      if ( empty( ) )
      {
        return nullptr;
      }
      Job::JobPtr j = _jobs.back( );
      _jobs.pop_back( );
      return j;
    }
    Job::JobPtr JobQueue::pop_back( void )
    {
      Lock lock( _mutex );
      if ( empty( ) )
      {
        return nullptr;
      }
      Job::JobPtr j = _jobs.front( );
      _jobs.erase( _jobs.begin( ) );
      return j;
    }

    // Global methods
    Job::JobPtr async( void )
    {
      auto job = std::make_shared< Job >( );
      job->reset( );
      return job;
    }
    Job::JobPtr async( const Job::JobPtr& parent,
      const Job::JobCallback& cb )
    {
      auto job = std::make_shared< Job >( );
      job->reset( parent, cb );
      JobScheduler::getInstance( )->schedule( job );
      return job;
    }
    void wait( const Job::JobPtr& job )
    {
      JobScheduler::getInstance( )->wait( job );
    }



    JobScheduler::JobScheduler( void )
    {
      configure( );
    }
    void JobScheduler::configure( int numWorkers )
    {
      int nw = numWorkers;
      if ( nw < 0 )
      {
        nw = std::thread::hardware_concurrency( );
      }
      _numWorkers = nw;
    }
    bool JobScheduler::start( void )
    {
      _state = State::INIT;

      initWorker( true );
      for ( unsigned int i = 0; i < _numWorkers; ++i )
      {
        _workers.push_back( std::thread(
          std::bind( &JobScheduler::worker, this ) )
        );
      }
      _state = State::RUN;
      return true;
    }
    void JobScheduler::stop( void )
    {
      _state = State::STOPPING;

      for ( auto& worker : _workers )
      {
        if ( worker.joinable( ) )
        {
          worker.join( );
        }
      }
      _workers.clear( );
      _workerJobQueues.clear( );
      _state = State::STOPPED;
    }
    void JobScheduler::worker( void )
    {
      initWorker( false );

      while ( getState( ) == State::INIT )
      {
        // wait for startup to complete
        yield( );
      }

      while ( getState( ) == State::RUN )
      {
        executeNextJob( );
      }
    }
    void JobScheduler::initWorker( bool mainWorker )
    {
      std::lock_guard<std::mutex> lock( _mutex );
      if ( mainWorker )
      {
        _mainWorkerID = getWorkerID( );
      }
      _workerJobQueues[ getWorkerID( ) ] = std::make_shared< JobQueue >( );
    }
  }
}
