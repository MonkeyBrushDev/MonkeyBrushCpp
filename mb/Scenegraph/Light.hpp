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

#ifndef __MB_LIGHT__
#define __MB_LIGHT__

#include <mb/api.h>
#include "Node.hpp"
#include "../Maths/Color.hpp"
#include "../Maths/Vector3.hpp"
#include "../Maths/Matrix4.hpp"

namespace mb
{
  class Light :
    public Node
  {
    enum class ShadowType
    {
      NONE,
      SOFT,
      HARD
    };
    enum class Type
    {
      //AMBIENT,
      DIRECTIONAL,
      HEMISPHERIC,
      POINT,
      SPOT
    };
  public:
    MB_API
    Light( Light::Type t = Light::Type::POINT );
    MB_API
    virtual ~Light( void );

    const Light::Type& getType( void ) const { return _type; }

    mb::Vector3 getPosition( void ) const
    {
      return getWorld( ).getPosition( );
    }
    mb::Vector3 getDirection( void ) const
    {
      if ( _type == Type::POINT )
      {
        return mb::Vector3::ZERO;
      }
      return getWorld( ).computeDirection( );
    }
    const Color& getColor( void ) { return _diffuseColor; }
    void setColor( const Color& c ) { _diffuseColor = c; }
    const Color& getGroundColor( void )
    {
      if ( _type == Type::HEMISPHERIC )
      {
        return _groundColor;
      }
      return mb::Color::BLACK;
    }
    void setGroundColor( const Color& c )
    {
      _groundColor = c;
    }

    mb::Matrix4 computeProjectionMatrix( void ) const
    {
      return mb::Matrix4::orthographic(
        -10.0f, 10.0f,
        -10.0f, 10.0f,
        _shadowFar, _shadowNear
      );
      /*const float top = _shadowFar;
      const float left = -_shadowFar;
      const float right;
      const float bottom = -_shadowFar;
      const float near;
      const float far;

      return mb::Matrix4({
        2.0f / ( right - left ), 0.0f, 0.0f, - ( right + left ) / ( right - left ),
        0.0f, 2.0f / ( top - bottom ), 0.0f, - ( top + bottom ) / ( top - bottom ),
        0.0f, 0.0f, -2.0f / ( far - near ), - ( far + near ) / ( far - near ),
        0.0f, 0.0f, 0.0f, 1.0f
      });*/
    }
    mb::Matrix4 computeViewMatrix( void ) const
    {
      return getWorld( ).computeModel( ).getInverse( );
    }

  public:
    MB_API
    virtual void accept( Visitor& v ) override;

  public:
    Light::Type _type;
    mb::Color _diffuseColor;
    mb::Color _ambientColor;
    mb::Color _groundColor;   // Only for hemispheric light
    ShadowType _shadowType;
    float strength = 1.0f;
    float bias = 0.05f;
    float normalBias = 0.4f;
    float nearPlane = 0.2f;
    // TODO: mb::Vector3 _attenuation;
    float _shadowNear = 0.1f;
    float _shadowFar = 1024.0f;
  };
  typedef std::shared_ptr<Light> LightPtr;
}

#endif /* __MB_LIGHT__ */
