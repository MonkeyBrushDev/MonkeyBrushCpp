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
      NO_SHADOW,
      SOFT_SHADOW,
      HARD_SHADOW
    };
    enum class Type
    {
      //AMBIENT,
      DIRECTIONAL,
      //HEMISPHERIC,
      POINT,
      SPOT
    };
  public:
    MB_API
    Light( Light::Type t = Light::Type::POINT );
    MB_API
    ~Light( void );

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

    /*mb::Matrix4 computeProjectionMatrix( void ) const
    {
      const float top;
      const float left;
      const float right;
      const float bottom;
      const float near;
      const float far;

      return mb::Matrix4({
        2.0f / ( right - left ), 0.0f, 0.0f, - ( right + left ) / ( right - left ),
        0.0f, 2.0f / ( top - bottom ), 0.0f, - ( top + bottom ) / ( top - bottom ),
        0.0f, 0.0f, -2.0f / ( far - near ), - ( far + near ) / ( far - near ),
        0.0f, 0.0f, 0.0f, 1.0f
      });
    }*/
    mb::Matrix4 computeViewMatrix( void ) const
    {
      return getWorld( ).computeModel( ).getInverse( );
    }

  public:
    MB_API
    virtual void accept( Visitor& v ) override;

  public:
    Light::Type _type;
    Color _diffuseColor;
    Color _ambientColor;
    ShadowType shadowType;
    float strength = 1.0f;
    float bias = 0.05f;
    float normalBias = 0.4f;
    float nearPlane = 0.2f;
  };
}

#endif /* __MB_LIGHT__ */
