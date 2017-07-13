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

#include "Window.hpp"
#include <string>

namespace mb
{
  WindowParams::WindowParams( int width_, int height_ )
  {
    this->width = width_;
    this->height = height_;
    this->displayFPS = true;
    this->displayMouse = true;
    this->debugWindowEvents = true;
    this->maxVersion = 4;
    this->minVersion = 3;
    this->resizable = true;
    this->depthBufferBit = 24;
    this->multiSample = 0;
    this->title = "Foo title";
  }
}
