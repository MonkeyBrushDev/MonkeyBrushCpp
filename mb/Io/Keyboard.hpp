/*
 * Copyright (c) 2016 maldicion069
 *
 * Authors: Cristian Rodríguez Bernal <ccrisrober@gmail.com>
 *
 * This file is part of MonkeyBrushPlusPlus
 * <https://github.com/maldicion069/monkeybrushplusplus>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#ifndef __MB_KEYBOARD__
#define __MB_KEYBOARD__

#include <mb/api.h>
#include <bitset>
#include "../Includes.hpp"

namespace mb
{
  class Keyboard
  {
  public:
    enum class Key
    {
      A,
      B,
      C,
      D,
      E,
      F,
      G,
      H,
      I,
      J,
      K,
      L,
      M,
      N,
      O,
      P,
      Q,
      R,
      S,
      T,
      U,
      V,
      W,
      X,
      Y,
      Z,
      Up,
      Down,
      Left,
      Right,
      F1,
      F2,
      F3,
      F4,
      F5,
      F6,
      F7,
      F8,
      F9,
      F10,
      F11,
      F12,
      Num1,
      Num2,
      Num3,
      Num4,
      Num5,
      Num6,
      Num7,
      Num8,
      Num9,
      Num0,
      Esc,
      Enter,
      Space,
      LShift,
      RShift,
      LAlt,
      RAlt,
      Plus,
      Minus,
      Multiply,
      Divide
    };

    virtual ~Keyboard();

    virtual bool keyPress(const Key& k) = 0;
    virtual bool keyRelease(const Key& k) = 0;
    virtual bool singleKeyPress(const Key& k) = 0;
    virtual void update() = 0;
  };
  class GLFWKeyboard : public Keyboard
  {
  public:
    MB_API
    void onKeyUp( int code );
    MB_API
    void onKeyDown( int code );
    MB_API
    virtual bool keyPress( const Key& k );
    MB_API
    virtual bool keyRelease( const Key& k );
    MB_API
    virtual bool singleKeyPress( const Key& k );
    MB_API
    virtual void update( );
  private:
    std::bitset<GLFW_KEY_LAST> _keyPreviusState;
    std::bitset<GLFW_KEY_LAST> _isKeyPressed;
    std::bitset<GLFW_KEY_LAST> _isKeyClicked;

    int ConvertFromKey( Keyboard::Key k );
  };
}

#endif /* __MB_KEYBOARD__ */
