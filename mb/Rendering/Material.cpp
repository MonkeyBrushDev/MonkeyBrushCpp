#include "Material.hpp"

namespace mb
{
  Material::~Material( void )
  {
  }
  TUniforms& Material::uniforms( void )
  {
    return this->_uniforms;
  }
  UniformPtr& Material::uniform( const std::string& name )
  {
    return this->_uniforms[ name ];
  }
  void Material::addUniform( const std::string& name, UniformPtr u )
  {
    this->_uniforms[ name ] = u;
  }
  bool Material::hasUniform( const std::string& name )
  {
    return _uniforms.find( name ) != _uniforms.end( );
  }
  UniformPtr Material::operator[ ]( const std::string& name )
  {
    return uniform( name );
  }
  void Material::use( void )
  {
    for ( const auto& uniform: _uniforms )
    {
      auto type = uniform.second->type( );
      if ( type == UniformType::Float )
      {

      }
      else if ( type == UniformType::Integer )
      {

      }
      else if ( type == UniformType::Matrix4 )
      {

      }
    }
  }
  void Material::unuse( void )
  {
  }
  PipelineState& Material::state( void )
  {
    return _state;
  }
  const PipelineState& Material::getState( void ) const
  {
    return _state;
  }
  void Material::state( const PipelineState &ps )
  {
    _state = ps;
  }
}
