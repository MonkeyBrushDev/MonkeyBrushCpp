#ifndef __MB_MATERIAL__
#define __MB_MATERIAL__

#include <memory>
#include <unordered_map>
#include <mb/api.h>

namespace mb
{
  MB_API
  enum UniformType
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
    Uniform( void ) { }
    MB_API
    UniformType type() const
    {
      return _type;
    }
  protected:
    UniformType _type;
  };

  typedef std::shared_ptr< Uniform > UniformPtr;

  typedef std::unordered_map< std::string, UniformPtr > TUniforms;
  class Material
  {
  public:
    MB_API
    virtual ~Material( void )
    {

    }
    MB_API
    TUniforms& uniforms( void )
    {
      return this->_uniforms;
    }
    MB_API
    UniformPtr& uniform( const std::string& name )
    {
      return this->_uniforms[ name ];
    }

    MB_API
    void addUniform( const std::string& name, UniformPtr u )
    {
      this->_uniforms[ name ] = u;
    }
    bool hasUniform( const std::string& name )
    {
      return _uniforms.find( name ) != _uniforms.end( );
    }
    MB_API
    UniformPtr operator[ ]( const std::string& name )
    {
      return uniform( name );
    }
    MB_API
    virtual void use( void )
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
    MB_API
    virtual void unuse( void )
    {

    }
  protected:
    TUniforms _uniforms;
  };

  typedef std::shared_ptr< Material > MaterialPtr;
}

#endif /* __MB_MATERIAL__ */
