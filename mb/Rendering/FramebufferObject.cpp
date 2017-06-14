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

#include "FramebufferObject.hpp"

namespace mb
{
  FramebufferObject::FramebufferObject( unsigned int w, unsigned int h )
    : _width( w )
    , _height( h )
    , _clearColor( mb::Color::BLACK )
  {
  }
  void FramebufferObject::resize( unsigned int w, unsigned int h )
  {
    _width = w;
    _height = h;
    // TODO: RESIZE RENDER TARGET
  }


  StandardFramebuffer::StandardFramebuffer( unsigned int w, unsigned int h )
    : FramebufferObject( w, h )
  {
    _renderTargets.insert(std::pair<std::string, RenderTarget>(
                            "color",
                            RenderTarget( w, h, RenderTarget::Type::RGBA, true ) ) );
  }

  StandardFramebuffer::~StandardFramebuffer( void )
  {

  }


  GBuffer::GBuffer( unsigned int w, unsigned int h )
    : FramebufferObject( w, h )
  {
    _renderTargets.insert(std::pair<std::string, RenderTarget>(
                            "position",
                            RenderTarget( w, h, RenderTarget::Type::RGBA, true ) ) );
    _renderTargets.insert(std::pair<std::string, RenderTarget>(
                            "normal",
                            RenderTarget( w, h, RenderTarget::Type::RGB, true ) ) );
    _renderTargets.insert(std::pair<std::string, RenderTarget>(
                            "color",
                            RenderTarget( w, h, RenderTarget::Type::RGBA, true ) ) );
  }

  GBuffer::~GBuffer( void )
  {

  }
}
