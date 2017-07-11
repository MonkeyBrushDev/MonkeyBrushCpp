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

#ifndef __MB_STANDARDMATERIAL__
#define __MB_STANDARDMATERIAL__

#include <mb/api.h>

#include "../Rendering/Material.hpp"
#include "../Rendering/Texture.hpp"
#include "../Maths/Color.hpp"
#include "../Maths/Vector4.hpp"

namespace mb
{
  class StandardMaterial: public Material
  {
  public:
    MB_API
    StandardMaterial( void );
    MB_API
    void setColor( const mb::Color &color );
    MB_API
    void setShininess( const float &v );
    MB_API
    void setNormalScale( const float &v );
    MB_API
    void setColorMap( mb::Texture2D *texture );
    MB_API
    void setSpecularMap( mb::Texture2D *texture );
    MB_API
    void setNormalMap( mb::Texture2D *texture );
  protected:
    mb::UniformPtr _diffuse;
    mb::UniformPtr _shininess;
    mb::UniformPtr _colorMap;
    mb::UniformPtr _normalMap;
    mb::UniformPtr _normalScale;
    mb::UniformPtr _specularMap;
  };
}

#endif /* __MB_STANDARDMATERIAL__ */
