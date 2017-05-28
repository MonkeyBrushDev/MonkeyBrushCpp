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

#ifndef __MB_INPUT__
#define __MB_INPUT__

#include <mb/api.h>

#include "Mouse.hpp"
#include "Keyboard.hpp"

namespace mb
{
  class Input
  {
  public:
    MB_API
    static void initialize();
    MB_API
    static void destroy();
    MB_API
    static mb::Keyboard* Keyboard();
    MB_API
    static mb::Mouse* Mouse();
    MB_API
    static bool isKeyPressed(Keyboard::Key key);
    MB_API
    static bool isKeyClicked(Keyboard::Key key);
    MB_API
    static bool KeyReleased(Keyboard::Key key);
    MB_API
    static int MouseX();
    MB_API
    static int MouseY();
    MB_API
    static Input* instance();
    MB_API
    static int PreviousMouseX();
    MB_API
    static int PreviousMouseY();
    MB_API
    static int MouseWheelX();
    MB_API
    static int MouseWheelY();
    MB_API
    static int DeltaX(int val);
    MB_API
    static int DeltaY(int val);
    MB_API
    static bool MouseButtonPress(MouseButton button);
    MB_API
    static bool MouseButtonSinglePress(MouseButton button);
    MB_API
    static bool MouseButtonRelease(MouseButton button);
    MB_API
    static void update();
  protected:
    mb::Keyboard* _keyboard;
    mb::Mouse*    _mouse;

    static Input *_instance;
  };
}

#endif /* __MB_INPUT__ */
