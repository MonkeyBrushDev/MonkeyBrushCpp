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
#include "../Maths/Vector2.hpp"
#include "../Maths/Vector3.hpp"
#include "../Maths/Vector4.hpp"
#include "../Maths/Matrix4.hpp"
#include "Texture.hpp"

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
    unsigned int texId = 0;
    program->use( );
    for ( const auto& uniform: _uniforms )
    {
      auto type = uniform.second->type( );
      if ( type == UniformType::Float )
      {
        program->sendUniformf(
          uniform.first,
          uniform.second->value( ).cast< float >( )
        );
      }
      else if ( type == UniformType::Integer )
      {
        program->sendUniformi(
          uniform.first,
          uniform.second->value( ).cast< int >( )
        );
      }
      else if ( type == UniformType::Vector2 )
      {
        program->sendUniform2v(
          uniform.first,
          uniform.second->value( ).cast< mb::Vector2 >( ).data( )
        );
      }
      else if ( type == UniformType::Vector3 )
      {
        program->sendUniform3v(
          uniform.first,
          uniform.second->value( ).cast< mb::Vector3 >( ).data( )//.data( )
        );
      }
      else if ( type == UniformType::Vector4 )
      {
        mb::Vector4 cc = uniform.second->value( ).cast< mb::Vector4 >( );
        program->sendUniform4v(
          uniform.first,
          cc.data( )//.data( )
        );
      }
      else if ( type == UniformType::Matrix4 )
      {
        program->sendUniform4m(
          uniform.first,
          uniform.second->value( ).cast< mb::Matrix4 >( ).data( )
        );
      }
      else if ( type == UniformType::TextureSampler )
      {
        mb::Texture* tex = uniform.second->value().cast< mb::Texture* >();
        if (tex == nullptr) continue;
        tex->bind(texId);
        this->program->sendUniformi(uniform.first, texId);
        ++texId;
        // TODO: UNBIND TEXTURES IN UNUSE METHOD
      }
    }
  }
  void Material::unuse( void )
  {
    program->unuse( );
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
