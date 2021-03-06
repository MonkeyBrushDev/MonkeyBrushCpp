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

#include "GreyImageEffect.hpp"
#include "../../Scenegraph/Camera.hpp"
#include "../Renderer.hpp"

namespace mb
{
  void GreyToneEffect::compute( Renderer*, Camera* )
  {

  }

  void GreyToneEffect::apply( Renderer*, Camera* /*camera*/ )
  {
    // bind shader, texture, draw and unbind texture and shader
    //std::cout << "Aplicando GreyToneEffect" << std::endl;
    std::cout << "Bind program (GreyToneEffect)" << std::endl;
    std::cout << "\tBind texture" << std::endl;
    std::cout << "\tDraw ScreenQuad" << std::endl;
    std::cout << "\tUnbind texture" << std::endl;
    std::cout << "Unbind program (GreyToneEffect)" << std::endl;
  }
}
