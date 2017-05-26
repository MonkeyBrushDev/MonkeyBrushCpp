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

#ifndef __MB_MATERIAL__
#define __MB_MATERIAL__

#include <memory>
#include <unordered_map>
#include <mb/api.h>

#include "../Utils/any.hpp"
#include "PipelineState.hpp"

namespace mb
{
  MB_API
  enum class UniformType
  {
    Invalid,
    Float, Integer, Unsigned, Boolean,
    Vector2, Vector3, Vector4,
    Matrix2, Matrix3, Matrix4,
    TextureSampler
  };

  class Uniform
  {
  public:
    MB_API
    Uniform( )
      : _type( UniformType::Invalid )
      , _value( )
    {
    }
    MB_API
    Uniform( UniformType type_, any value_ = nullptr )
      : _type( type_ )
      , _value( value_ )
    {
    }
    MB_API
    Uniform( const Uniform& other )
      : _type( other._type )
      , _value( other._value )
    {
    }
    MB_API
    any value( ) const
    {
      return this->_value;
    }
    MB_API
    void value( const any v )
    {
      _value = std::move( v );
    }
    MB_API
    UniformType type() const
    {
      return _type;
    }
  protected:
    UniformType _type;
    any _value;
  };

  typedef std::shared_ptr< Uniform > UniformPtr;

  typedef std::unordered_map< std::string, UniformPtr > TUniforms;
  class Material
  {
  public:
    MB_API
    virtual ~Material( void );
    MB_API
    TUniforms& uniforms( void );
    MB_API
    UniformPtr& uniform( const std::string& name );
    MB_API
    void addUniform( const std::string& name, UniformPtr u );
    MB_API
    bool hasUniform( const std::string& name );
    MB_API
    UniformPtr operator[ ]( const std::string& name );
    MB_API
    virtual void use( void );
    MB_API
    virtual void unuse( void );
    MB_API
    const PipelineState &getState( void ) const;
    MB_API
    PipelineState &state( void );
    MB_API
    void state( const PipelineState &ps );
  protected:
    TUniforms _uniforms;
    PipelineState _state;
  };

  typedef std::shared_ptr< Material > MaterialPtr;
}

#endif /* __MB_MATERIAL__ */
