#include <iostream>
#include <mb/mb.h>
using namespace mb;

#include <thread>
#include <memory>

int main( )
{
  auto comp = new ParticleEffectComponent( 5 );
  comp->addGenerator( std::make_shared< SpherePositionParticleGenerator>( ) );
  comp->addGenerator( std::make_shared< SphereVelocityParticleGenerator>( ) );
  comp->addGenerator( std::make_shared< TimeParticleGenerator>( ) );
  comp->addUpdater( std::make_shared< TimeParticleUpdater>( ) );
  comp->addUpdater( std::make_shared< PositionVelocityParticleUpdater>( ) );
  comp->addRenderer( std::make_shared<PrintRenderer>( ) );
  comp->start( );

  float aux = 0.0f;
  while ( aux < 1.0f )
  {
    std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
    aux += 0.1f;
    comp->update( 0.1f );
  }

  comp->update( 0.1f );
  system( "PAUSE" );
  return 0;
}
