#ifndef __MB_PARTICLE_EFFECT_COMPONENT__
#define __MB_PARTICLE_EFFECT_COMPONENT__

#include "Component.hpp"

#include <mb/api.h>
#define NOMINMAX

#include <algorithm>
#include <map>
#include <vector>
#include <memory>

#include "../Maths/Vector3.hpp"

namespace mb
{
  enum ParticleAttrType
  {
    POSITION,
    VELOCITY,
    ACCELERATION,
    COLOR,
    TIME
  };

  typedef unsigned int ParticleID;

  class IParticleAttrArray
  {
  public:
    template< typename T >
    T &operator[]( unsigned int idx )
    {
      return static_cast< T* >( _data.at( idx ) );
    }
    template< typename T >
    const T &operator[]( unsigned int idx ) const
    {
      return static_cast< T* >( _data.getData( ) )[ idx ];
    }

    MB_API
    virtual unsigned int getCount( void ) const = 0;
    MB_API
    virtual void reset( unsigned int count ) = 0;
    MB_API
    virtual void swap( ParticleID a, ParticleID b ) = 0;
    MB_API
    virtual void *rawData( void ) = 0;
    MB_API
    virtual const void *rawData( void ) const = 0;

    template< typename T >
    T* getData( void )
    {
      return static_cast< T* >( rawData( ) );
    }

    template< typename T >
    const T* getData( void ) const
    {
      return static_cast< T* >( rawData( ) );
    }
  };
  typedef std::shared_ptr< IParticleAttrArray > IParticleAttrArrayPtr;

  template< typename T >
  class ParticleAttrArray : public IParticleAttrArray
  {
  public:
    virtual unsigned int getCount( void ) const override
    {
      return _data.size( );
    }
    virtual void reset( unsigned int count ) override
    {
      _data.resize( count );
    }
    virtual void swap( ParticleID a, ParticleID b ) override
    {
      std::swap( _data[ a ], _data[ b ] );
    }
    virtual void *rawData( void ) override
    {
      return _data.data( );
    }
    virtual const void *rawData( void ) const override
    {
       return _data.data( );
    }
  protected:
    std::vector< T > _data;
  };

  class ParticleInfo
  {
  public:
    ParticleInfo( unsigned int maxParticles )
      : _maxParticles( maxParticles )
    {
      _alives.resize( _maxParticles, false );
    }
    template< typename T >
    IParticleAttrArray* createAttributeArray( ParticleAttrType attrType )
    {
      auto attribute = getAttribute( attrType );
      if ( attribute == nullptr )
      {
        attribute = std::make_shared<ParticleAttrArray< T > >( );
        setAttribute( attrType, attribute );
      }
      return attribute.get( );
    }
    void generate( void )
    {
      _alivesParticles = 0;
      unsigned int numParticles = getNumParticles( );
      for ( auto& attr : _attributes )
      {
        attr.second->reset( numParticles );
      }
      std::fill( _alives.begin( ), _alives.end( ), false );
    }
    unsigned int getNumParticles( void )
    {
      return _maxParticles;
    }
    unsigned int getNumAliveParticles( void )
    {
      return _alivesParticles;
    }
    bool isAlive( ParticleID id )
    {
      return _alives[ id ];
    }
    void setAttribute( ParticleAttrType attrType,
      const IParticleAttrArrayPtr& attrArray )
    {
      _attributes[ attrType ] = attrArray;
    }
    IParticleAttrArrayPtr getAttribute( ParticleAttrType attrType )
    {
      return _attributes[ attrType ];
    }
    void kill( ParticleID id )
    {
      _alives[ id ] = false;
      swap( id, --_alivesParticles );
    }
    void wakeUp( ParticleID id )
    {
      _alives[ id ] = true;
      swap( id, _alivesParticles );
      ++_alivesParticles;
    }
    void swap( ParticleID a, ParticleID b )
    {
      if ( a != b )
      {
        for ( auto& attr : _attributes )
        {
          attr.second->swap( a, b );
        }
        std::swap( _alives[ a ], _alives[ b ] );
      }
    }
  protected:
    std::map<ParticleAttrType, IParticleAttrArrayPtr> _attributes;
    std::vector<bool> _alives;
    unsigned int _maxParticles;
    unsigned int _alivesParticles;
  };
  typedef std::shared_ptr< ParticleInfo > ParticlesInfoPtr;
  class ParticleUpdater
  {
  public:
    virtual void configure( ParticlesInfoPtr particles ) = 0;
    virtual void update( const float&, ParticlesInfoPtr particles ) = 0;
  };
  typedef std::shared_ptr< ParticleUpdater > ParticleUpdaterPtr;
  class ParticleRenderer
  {
  public:
    virtual void configure( ParticlesInfoPtr particles ) = 0;
    virtual void update( const float&, ParticlesInfoPtr particles ) = 0;
  };
  typedef std::shared_ptr< ParticleRenderer > ParticleRendererPtr;
  class ParticleGenerator
  {
  public:
    virtual void configure( ParticlesInfoPtr particles ) = 0;
    virtual void generate( const float&, ParticlesInfoPtr particles,
      unsigned int start, unsigned int end ) = 0;
  };
  typedef std::shared_ptr< ParticleGenerator > ParticleGeneratorPtr;


  class SphereVelocityParticleGenerator : public ParticleGenerator
  {
  public:
    virtual void configure( ParticlesInfoPtr particles ) override
    {
      _velocities = particles->createAttributeArray< Vector3 >( ParticleAttrType::VELOCITY );

      _magnitude = Vector3( 1.0f );
    }
    virtual void generate( const float&, ParticlesInfoPtr particles,
      unsigned int start, unsigned int end ) override
    {
      auto vs = _velocities->getData< Vector3 >( );

      const auto posMin = Vector3( -1.0f );
      const auto posMax = Vector3( 1.0f );

      for ( unsigned int i = start; i < end; ++i )
      {
        auto x = RandomFloat( posMin.x( ), posMax.x( ) );
        auto y = RandomFloat( posMin.y( ), posMax.y( ) );
        auto z = RandomFloat( posMin.z( ), posMax.z( ) );
        vs[ i ] = Vector3( x, y, z ).getNormalized( ) * _magnitude;
      }
    }
  protected:
    float RandomFloat( float min, float max )
    {
      float r = ( float ) rand( ) / ( float ) RAND_MAX;
      return min + r * ( max - min );
    }
    Vector3 _magnitude;
    IParticleAttrArray* _velocities;
  };

  class SpherePositionParticleGenerator : public ParticleGenerator
  {
  public:
    virtual void configure( ParticlesInfoPtr particles ) override
    {
      _positions = particles->createAttributeArray< Vector3 >( ParticleAttrType::POSITION );

      _origin = Vector3( 0.0f );
      _size = Vector3( 0.1f );
    }
    virtual void generate( const float&, ParticlesInfoPtr particles,
      unsigned int start, unsigned int end ) override
    {
      auto ps = _positions->getData< Vector3 >();

      const auto posMin = Vector3( -1.0f );
      const auto posMax = Vector3( 1.0f );

      for ( unsigned int i = start; i < end; ++i )
      {
        auto x = RandomFloat( posMin.x( ), posMax.x( ) );
        auto y = RandomFloat( posMin.y( ), posMax.y( ) );
        auto z = RandomFloat( posMin.z( ), posMax.z( ) );
        ps[ i ] = _origin + Vector3( x, y, z ).getNormalized() * _size;
      }
    }
  protected:
    float RandomFloat( float min, float max )
    {
      float r = ( float ) rand( ) / ( float ) RAND_MAX;
      return min + r * ( max - min );
    }
    Vector3 _origin;
    Vector3 _size;
    IParticleAttrArray* _positions;
  };


  class TimeParticleGenerator : public ParticleGenerator
  {
  public:
    virtual void configure( ParticlesInfoPtr particles ) override
    {
      _times = particles->createAttributeArray< float >( ParticleAttrType::TIME );
    }
    virtual void generate( const float&, ParticlesInfoPtr particles,
      unsigned int start, unsigned int end ) override
    {
      float* ts = _times->getData< float >( );
      for ( unsigned int i = start; i < end; ++i )
      {
        float t = RandomFloat( 0.1f, 2.0f );
        ts[ i ] = t;
      }
    }
  protected:
    float RandomFloat( float min, float max )
    {
      float r = ( float ) rand( ) / ( float ) RAND_MAX;
      return min + r * ( max - min );
    }
    IParticleAttrArray* _times;
  };

  class AccelerationParticleGenerator : public ParticleGenerator
  {
  public:
    virtual void configure( ParticlesInfoPtr particles ) override
    {
      _accelerations = particles->createAttributeArray< Vector3 >( ParticleAttrType::ACCELERATION );

      _minAcceleration = Vector3( 0.0f );
      _maxAcceleration = Vector3( 1.0f );
    }
    virtual void generate( const float&, ParticlesInfoPtr particles,
      unsigned int start, unsigned int end ) override
    {
      auto as = _accelerations->getData< Vector3 >( );

      for ( unsigned int i = start; i < end; ++i ) {
        as[ i ][ 0 ] = RandomFloat( _minAcceleration.x( ), _maxAcceleration.x( ) );
        as[ i ][ 1 ] = RandomFloat( _minAcceleration.y( ), _maxAcceleration.y( ) );
        as[ i ][ 2 ] = RandomFloat( _minAcceleration.z( ), _maxAcceleration.z( ) );
      }
    }
  protected:
    float RandomFloat( float min, float max )
    {
      float r = ( float ) rand( ) / ( float ) RAND_MAX;
      return min + r * ( max - min );
    }
    Vector3 _minAcceleration;
    Vector3 _maxAcceleration;
    IParticleAttrArray* _accelerations;
  };

  class PositionVelocityParticleUpdater : public ParticleUpdater
  {
  public:
    virtual void configure( ParticlesInfoPtr particles ) override
    {
      _positions = particles->createAttributeArray< Vector3 >( ParticleAttrType::POSITION );
      _velocities = particles->createAttributeArray< Vector3 >( ParticleAttrType::VELOCITY );
    }
    virtual void update( const float& dt, ParticlesInfoPtr particles ) override
    {
      const unsigned int count = particles->getNumAliveParticles( );

      auto ps = _positions->getData< Vector3 >( );
      auto vs = _velocities->getData< Vector3 >( );

      for ( unsigned int i = 0; i < count; ++i )
      {
        Vector3 v = vs[ i ] * dt;
        ps[ i ] += v;
      }
    }
  protected:
    IParticleAttrArray* _positions;
    IParticleAttrArray* _velocities;
  };

  class TimeParticleUpdater : public ParticleUpdater
  {
  public:
    virtual void configure( ParticlesInfoPtr particles ) override
    {
      _times = particles->createAttributeArray<float>( ParticleAttrType::TIME );
    }
    virtual void update( const float& dt, ParticlesInfoPtr particles ) override
    {
      const unsigned int count = particles->getNumAliveParticles( );

      float* ts = _times->getData< float >( );

      for ( unsigned int i = 0; i < count; ++i )
      {
        ts[ i ] -= dt;
        if ( ts[ i ] <= 0.0f )
        {
          particles->kill( i );
        }
      }
    }
  protected:
    IParticleAttrArray* _times;
  };

  class PrintRenderer : public ParticleRenderer
  {
  public:
    virtual void configure( ParticlesInfoPtr particles ) override
    {
      _positions = particles->createAttributeArray< Vector3 >( ParticleAttrType::POSITION );
      _times = particles->createAttributeArray<float>( ParticleAttrType::TIME );
    }
    virtual void update( const float&, ParticlesInfoPtr particles ) override
    {
      const unsigned int count = particles->getNumParticles( ); // getNumAliveParticles( );

      Vector3* pts = _positions->getData< Vector3 >( );
      float* ts = _times->getData< float >( );

      for ( unsigned int i = 0; i < count; ++i )
      {
        std::cout << "POSITION: (" << pts[ i ].x( ) << ", " << 
          pts[ i ].y( ) << ", " << pts[ i ].z( ) << ") ";
        if ( particles->isAlive( i ) )
        {
          std::cout << "\tTIME: " << ts[ i ] << std::endl;
        }
        else
        {
          std::cout << "\t ... died" << std::endl;
        }
      }
      std::cout << " ------ ------ ------ ------ ------ " << std::endl;
    }
  protected:
    IParticleAttrArray* _positions;
    IParticleAttrArray* _times;
  };

  class ParticleEffectComponent : public Component
  {
    IMPLEMENT_COMPONENT( ParticleEffectComponent )
  public:
    MB_API
    ParticleEffectComponent( unsigned int numParticles );
    MB_API
    virtual void start( void ) override;
    MB_API
    virtual void update( const float &dt ) override;
    MB_API
    void addGenerator( const ParticleGeneratorPtr& gen );
    MB_API
    void addUpdater( const ParticleUpdaterPtr& upd );
    MB_API
    void addRenderer( const ParticleRendererPtr& rnd );
    std::string textureName;
  protected:
    void updateGenerators( const float& dt )
    {
      unsigned int maxNewParticles = _particleInfo->getNumParticles( ); // ??
      unsigned int start = _particleInfo->getNumAliveParticles( );
      unsigned int end = std::min( start + maxNewParticles,
        _particleInfo->getNumParticles( ) );
      for ( auto& gen : _generators )
      {
        gen->generate( dt, _particleInfo, start, end );
      }
      for ( unsigned int id = start; id < end; ++id )
      {
        _particleInfo->wakeUp( id );
      }
    }
    void updateUpdaters( const float& dt )
    {
      for ( auto& upd : _updaters )
      {
        upd->update( dt, _particleInfo );
      }
    }
    void updateRenderers( const float& dt )
    {
      for ( auto& rend : _renderers )
      {
        rend->update( dt, _particleInfo );
      }
    }
    float getWarmTime( void ) const
    {
      return _warmTime;
    }
    void setWarmTime( const float& time )
    {
      _warmTime = time;
    }
  protected:
    float _warmTime = 0.0f;
    unsigned int numParticles;
    ParticlesInfoPtr _particleInfo;
    std::vector< ParticleGeneratorPtr > _generators;
    std::vector< ParticleUpdaterPtr > _updaters;
    std::vector< ParticleRendererPtr > _renderers;
  };
}

#endif /* __MB_PARTICLE_EFFECT_COMPONENT__ */
