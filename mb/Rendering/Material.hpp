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

#define MB_MODEL_MATRIX "MB_MATRIXM"
#define MB_VIEW_MATRIX "MB_MATRIXV"
#define MB_VIEWPROJ_MATRIX "MB_MATRIXVP"  // Unused
#define MB_PROJ_MATRIX "MB_MATRIXP"

#include <memory>
#include <unordered_map>
#include <mb/api.h>

#include "../Utils/any.hpp"
#include "PipelineState.hpp"

#include "../OpenGL/Program.hpp"

#include <iterator>
#include <algorithm>

#include "../Maths/Vector2.hpp"
#include "../Maths/Vector3.hpp"
#include "../Maths/Vector4.hpp"
#include "../Maths/Matrix4.hpp"
#include "../Rendering/Texture.hpp"

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
    explicit Uniform( void )
      : _type( UniformType::Invalid )
      , _value( )
    {
    }
    MB_API
    Uniform( const Uniform& other )
      : _type( other._type )
      , _value( other._value )
    {
    }
    Uniform* clone( void )
    {
      return new Uniform( *this );
    }
    MB_API
    any value( void ) const
    {
      return this->_value;
    }
    MB_API
    void value( const any v )
    {
      _value = std::move( v );
    }
    MB_API
    UniformType type( void ) const
    {
      return _type;
    }
  protected:
    UniformType _type;
    any _value;
  public:
    // TODO: REMOVE OR PROTECT THIS CTOR
    Uniform( UniformType type_, any value_ = nullptr )
      : _type( type_ )
      , _value( value_ )
    { }
  };
  typedef std::shared_ptr< Uniform > UniformPtr;

  class FloatUniform : public Uniform
  {
  public:
    MB_API
    FloatUniform( float v = 0.0f )
      : Uniform( UniformType::Float, v )
    { }
  };
  class IntegerUniform : public Uniform
  {
  public:
    MB_API
    IntegerUniform( int v = 0 )
      : Uniform( UniformType::Integer, v )
    { }
  };
  class UnsignedUniform : public Uniform
  {
  public:
    MB_API
    UnsignedUniform( unsigned int v = 0 )
      : Uniform( UniformType::Unsigned, v )
    { }
  };
  class BooleanUniform : public Uniform
  {
  public:
    MB_API
    BooleanUniform( bool v = false )
      : Uniform( UniformType::Boolean, v )
    { }
  };
  class Vector2Uniform : public Uniform
  {
  public:
    MB_API
    Vector2Uniform( const mb::Vector2& v = mb::Vector2( ) )
      : Uniform( UniformType::Vector2, v )
    { }
  };
  class Vector3Uniform : public Uniform
  {
  public:
    MB_API
    Vector3Uniform( const mb::Vector3& v = mb::Vector3( ) )
      : Uniform( UniformType::Vector3, v )
    { }
  };
  class Vector4Uniform : public Uniform
  {
  public:
    MB_API
    Vector4Uniform( const mb::Vector4& v = mb::Vector4( ) )
      : Uniform( UniformType::Vector4, v )
    { }
  };
  class Matrix4Uniform : public Uniform
  {
  public:
    MB_API
    Matrix4Uniform( const mb::Matrix4& v = mb::Matrix4( ) )
      : Uniform( UniformType::Matrix4, v )
    { }
  };
  class TextureUniform : public Uniform
  {
  public:
    MB_API
    TextureUniform( mb::Texture* v = nullptr )
    : Uniform( UniformType::TextureSampler, v )
    { }
  };

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

    MB_API
    Material( void )
    {
      program = std::make_shared< mb::Program >( );
    }
    MB_API
    Material( const mb::Material& m )
    {
      for ( auto& kv : m._uniforms )
      {
        this->addUniform( kv.first, UniformPtr( kv.second->clone( ) ) );
      }

      this->_state = m._state;
      this->program = m.program;
    }

    virtual Material* clone( void ) const
    {
      return new Material( *this );
    }

    std::shared_ptr< mb::Program > program;
  protected:
    unsigned int texId;
    TUniforms _uniforms;
    PipelineState _state;

  public:
    void addStandardUniforms( void )
    {
      addUniform( MB_PROJ_MATRIX, std::make_shared< mb::Matrix4Uniform >( ) );
      addUniform( MB_VIEW_MATRIX, std::make_shared< mb::Matrix4Uniform >( ) );
      addUniform( MB_MODEL_MATRIX, std::make_shared< mb::Matrix4Uniform >( ) );
    }
  };

  typedef std::shared_ptr< Material > MaterialPtr;
}

#endif /* __MB_MATERIAL__ */
