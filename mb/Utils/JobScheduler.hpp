#ifndef __MB_JOB_SCHEDULER__
#define __MB_JOB_SCHEDULER__

#include <functional>
#include <atomic>
#include <thread>
#include <vector>
#include <memory>
#include <mutex>
#include <map>
#include <iostream>
#include "Singleton.hpp"

namespace mb
{
  namespace concurrency
  {
    class Job
    {
    public:
      using JobPtr = std::shared_ptr< Job >;
      using JobCallback = std::function<void( void ) >;
      MB_API
      Job( void )
        : _callback( nullptr )
        , _parent( nullptr )
        , _unfinishedJobs( 0 )
      {
      }
      MB_API
      void reset( void )
      {
        _callback = nullptr;
        _parent = nullptr;
        _unfinishedJobs = 0;
      }
      MB_API
      void reset( const JobCallback& callback )
      {
        _callback = callback;
        _unfinishedJobs = 1;
      }
      MB_API
      void execute( void )
      {
        if( _callback != nullptr )
        {
          _callback( );
        }
        finish( );
      }
      MB_API
      void finish( void )
      {
        //if( _unfinishedJobs > 0 )
        //{
          --_unfinishedJobs;
        //}
        if( isCompleted( ) )
        {
          if( _parent != nullptr )
          {
            _parent->finish( );
          }
          _callback = nullptr;
        }
      }
      MB_API
      bool isCompleted( void ) const
      {
        return _unfinishedJobs == 0;
      }
      MB_API
      Job* getParent( void ) const
      {
        return _parent;
      }
    protected:
      JobCallback _callback;
      Job* _parent = nullptr;
      std::atomic< unsigned int > _unfinishedJobs;
    };


    class JobQueue
    {
      using Mutex = std::mutex;
      using Lock = std::lock_guard< Mutex >;
    public:
      std::size_t size( void );
      bool empty( void ) const;
      void push( const Job::JobPtr& job );
      Job::JobPtr pop( void );
      Job::JobPtr steal( void );
    protected:
      std::mutex _mutex;
      std::vector< Job::JobPtr > _jobs;
    };
    
    class JobScheduler: public Singleton < JobScheduler >
    {
    public:
      enum class State
      {
        INIT,
        RUN,
        STOPPING,
        STOPPED
      };
    protected:
      State _state = State::INIT;
      std::vector< std::thread > _workers;
      std::thread::id _mainWorkerID;
      std::mutex _mutex;
      unsigned int _numWorkers;
    public:
      JobScheduler( void )
      {
        configure( );
      }
      void configure( int numWorkers = -1 )
      {
        int nw = numWorkers;
        if ( nw < 0 )
        {
          nw = std::thread::hardware_concurrency( );
        }
        _numWorkers = nw;
      }
      MB_API
      bool start( void )
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
      MB_API
      void stop( void )
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
      void worker( void )
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
      void initWorker( bool mainWorker )
      {
        std::lock_guard<std::mutex> lock( _mutex );
        if ( mainWorker )
        {
          _mainWorkerID = std::this_thread::get_id( );
        }
        _workerJobQueues[ getWorkerId( ) ] = std::make_shared< JobQueue >( );
      }
      bool isRunning( void )
      {
        return _state == State::RUN;
      }
      State getState( void ) const
      {
        return _state;
      }
      std::thread::id JobScheduler::getWorkerId( void ) const
      {
        return std::this_thread::get_id( );
      }
      std::shared_ptr<JobQueue> getWorkerJobQueue( void )
      {
        return _workerJobQueues[ getWorkerId( ) ];
      }
      std::shared_ptr<JobQueue> getRandomJobQueue( void )
      {
        if ( _workerJobQueues.empty( ) )
        {
          return nullptr;
        }

        for ( auto &it : _workerJobQueues )
        {
          if ( it.second != nullptr && !it.second->empty( ) )
          {
            return it.second;
          }
        }
        return nullptr;
      }

      void schedule( const Job::JobPtr& job )
      {
        if ( job == nullptr )
        {
          return;
        }

        if ( getState( ) == State::STOPPING || getState( ) == State::STOPPED )
        {
          return;
        }
        auto queue = getWorkerJobQueue( );
        queue->push( job );
      }
      void wait( const Job::JobPtr& job )
      {
        while ( !job->isCompleted( ) )
        {
          executeNextJob( );
        }
      }
    protected:
      std::map< std::thread::id, std::shared_ptr< JobQueue >> _workerJobQueues;

      Job::JobPtr getJob( void )
      {
        auto queue = getWorkerJobQueue( );

        if ( queue != nullptr && !queue->empty( ) )
        {
          auto job = queue->pop( );
          if ( job != nullptr )
          {
            return job;
          }
        }

        auto stealQueue = getRandomJobQueue( );
        if ( stealQueue == nullptr || stealQueue == queue )
        {
          // do not steal from ourselves
          return nullptr;
        }

        if ( !stealQueue->empty( ) )
        {
          return stealQueue->steal( );
        }

        return nullptr;
      }
      bool executeNextJob( void )
      {
        auto job = getJob( );
        if (job != nullptr)
        {
          execute( job );
          return true;
        }
        yield( );
        return false;
      }
      void execute( const Job::JobPtr& job )
      {
        job->execute( );
      }
      void yield( void )
      {
        std::this_thread::yield( );
      }
    };
    MB_API
    Job::JobPtr async( void );
    MB_API
    Job::JobPtr async( const Job::JobPtr& parent, const Job::JobCallback& cb );
    MB_API
    void wait( const Job::JobPtr& job );
  }
}

#endif /* __MB_JOB_SCHEDULER__ */