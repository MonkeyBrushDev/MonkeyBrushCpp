#include "MaterialComponent.hpp"
#include <algorithm>

namespace mb
{
  MaterialComponent::~MaterialComponent( void )
  {
    removeMaterials( );
  }
  void MaterialComponent::addMaterial( mb::MaterialPtr  material )
  {
    _materials.push_back( material );
  }
  void MaterialComponent::removeMaterials( void )
  {
    _materials.clear( );
  }
  void MaterialComponent::eachMaterial( std::function< void ( mb::MaterialPtr ) > cb )
  {
    std::for_each( _materials.begin( ), _materials.end( ), [&] ( MaterialPtr m )
    {
      cb ( m );
    } );
  }
}
