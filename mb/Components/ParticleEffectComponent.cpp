#include "ParticleEffectComponent.hpp"

namespace mb
{
  ParticleEffectComponent::ParticleEffectComponent( unsigned int numParticles )
    : Component( )
  {
    textureName = "flare";
    _particleInfo = std::make_shared<ParticleInfo>( numParticles );
  }
  void ParticleEffectComponent::start( void )
  {
    for ( auto& gen : _generators )
    {
      gen->configure( _particleInfo );
    }
    for ( auto& upd : _updaters )
    {
      upd->configure( _particleInfo );
    }
    for ( auto& ren : _renderers )
    {
      ren->configure( _particleInfo );
    }
    _particleInfo->generate( );

    auto aux = _warmTime;
    const float tickTime = 1.0f / 60.0f;
    while ( aux > 0.0f )
    {
      updateGenerators( tickTime );
      updateUpdaters( tickTime );
      aux -= tickTime;
    }
  }
  void ParticleEffectComponent::update( const float &dt )
  {
    updateGenerators( dt );
    updateUpdaters( dt );
    updateRenderers( dt );
  }
  void ParticleEffectComponent::addGenerator( const ParticleGeneratorPtr& gen )
  {
    _generators.push_back( gen );
  }
  void ParticleEffectComponent::addUpdater( const ParticleUpdaterPtr& upd )
  {
    _updaters.push_back( upd );
  }
  void ParticleEffectComponent::addRenderer( const ParticleRendererPtr& rnd )
  {
    _renderers.push_back( rnd );
  }
}
