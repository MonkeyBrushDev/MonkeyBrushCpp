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
    Job::JobPtr JobQueue::steal( void )
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
      job->reset( cb );
      JobScheduler::getInstance( )->schedule( job );
      return job;
    }
    void wait( const Job::JobPtr& job )
    {
      JobScheduler::getInstance( )->wait( job );
    }
  }
}
