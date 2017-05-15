#include "Component.hpp"

#include <bitset>

namespace mb
{
  enum ParticleAttrType
  {
    POSITION,
    VELOCITY,
    COLOR
  };

  typedef unsigned int ParticleID;

  template< typename T >
  class ParticleAttrArray
  {
  public:
    template< typename T >
    T &operator[]( unsigned int idx )
    {
      return static_cast< T* >( _data.getData( ) )[ idx ];
    }
    template< typename T >
    const T &operator[]( unsigned int idx ) const
    {
      return static_cast< T* >( _data.getData( ) )[ idx ];
    }
    template< typename T >
    T* getData( void )
    {
      return static_cast< T* >( _data.getData( ) );
    }
    template< typename T >
    const T* getData( void ) const
    {
      return static_cast< T* >( _data.getData( ) );
    }
    virtual unsigned int getCount( void ) const
    {
      return _data.size( );
    }

    virtual void reset( unsigned int count )
    {
      _data.resize( count );
    }

    virtual void swap( ParticleID a, ParticleID b )
    {
      std::swap( _data[ a ], _data[ b ] );
    }
  protected:
    std::vector< T > _data;
  };

  class Particle
  {
  public:
    Particle( )
    {
      _alive.reset( 1000 );
    }
    ///std::map<ParticleAttrType, std::shared_ptr<ParticleAttrArray>> _particleData;
    std::bitset<1> _alive;
  };
  typedef std::shared_ptr< Particle > ParticlePtr;
  class ParticleUpdater
  {
  public:
    virtual void update( const float& ) = 0;
  };
  typedef std::shared_ptr< ParticleUpdater > ParticleUpdaterPtr;
  class ParticleRenderer
  {
  public:
    virtual void update( const float& ) = 0;
  };
  typedef std::shared_ptr< ParticleRenderer > ParticleRendererPtr;
  class ParticleGenerator 
  {
  public:
    virtual void generate( const float& ) = 0;
  };
  typedef std::shared_ptr< ParticleGenerator > ParticleGeneratorPtr;

  class ParticleEffectComponent : public Component
  {
  public:
    IMPLEMENT_COMPONENT( ParticleEffectComponent )
    MB_API
    ParticleEffectComponent( )
    {
      textureName = "flare";
      numParticles = 1000;
      _particles.reserve( numParticles );
    }
    MB_API
    virtual void start( void )
    {

    }
    MB_API
    virtual void update( const float &dt )
    {

    }
    MB_API
    void addGenerator( const ParticleGeneratorPtr& gen )
    {
      _generators.push_back( gen );
    }
    MB_API
    void addUpdater( const ParticleUpdaterPtr& upd )
    {
      _updaters.push_back( upd );
    }
    MB_API
    void addRenderer( const ParticleRendererPtr& rnd )
    {
      _renderers.push_back( rnd );
    }
    std::string textureName;
  protected:
    unsigned int numParticles;
    std::vector< ParticlePtr > _particles;
    std::vector< ParticleGeneratorPtr > _generators;
    std::vector< ParticleUpdaterPtr > _updaters;
    std::vector< ParticleRendererPtr > _renderers;
  protected:
    void updateGenerators( const float& dt )
    {
      for ( auto& gen : _generators )
      {
        gen->generate( dt );
      }
    }
    void updateUpdaters( const float& dt )
    {
      for ( auto& upd : _updaters )
      {
        upd->update( dt );
      }
    }
    void updateRenderers( const float& dt )
    {
      for ( auto& rend : _renderers )
      {
        rend->update( dt );
      }
    }
  };
}