/**
 * Copyright (c) 2017, Monkey Brush
 * All rights reserved.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

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
