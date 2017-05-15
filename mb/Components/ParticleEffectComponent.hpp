#include "Component.hpp"

namespace mb
{
  class Particle
  {
  };
  typedef std::shared_ptr< Particle > ParticlePtr;
  class ParticleUpdater
  {
  public:
    virtual void configure( void ) = 0;
    virtual void update( void ) = 0;
  };
  typedef std::shared_ptr< ParticleUpdater > ParticleUpdaterPtr;
  class ParticleRenderer
  {
  public:
    virtual void configure( void ) = 0;
    virtual void update( void ) = 0;
  };
  typedef std::shared_ptr< ParticleRenderer > ParticleRendererPtr;
  class ParticleGenerator 
  {
  public:
    virtual void configure( void ) = 0;
    virtual void generate( void ) = 0;
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
    void updateGenerators( )
    {
      for ( auto& gen : _generators )
      {
        gen->generate( );
      }
    }
    void updateUpdaters( )
    {
      for ( auto& upd : _updaters )
      {
        upd->update( );
      }
    }
    void updateRenderers( )
    {
      for ( auto& rend : _renderers )
      {
        rend->update( );
      }
    }
  };
}