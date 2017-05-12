#ifndef __MB_MATERIAL_COMPONENT__
#define __MB_MATERIAL_COMPONENT__

#include "Component.hpp"
#include <mb/api.h>
#include <vector>
#include <functional>
#include "../Rendering/Material.hpp"

namespace mb
{
  class MaterialComponent : public Component
  {
    IMPLEMENT_COMPONENT( MaterialComponent )
  public:
    MB_API
    virtual ~MaterialComponent( );
    MB_API
    bool hasMaterials( void ) const { return !_materials.empty( ); }
    MB_API
    void addMaterial( MaterialPtr material );
    // TODO: void removeMaterial( const unsigned int& idx );
    // TODO: void removeMaterial( const Material* material );
    MB_API
    void removeMaterials( void );
    MB_API
    void eachMaterial( std::function< void( mb::MaterialPtr ) > callback );
  private:
    std::vector< mb::MaterialPtr > _materials;
  };
}

#endif /* __MB_MATERIAL_COMPONENT__ */
