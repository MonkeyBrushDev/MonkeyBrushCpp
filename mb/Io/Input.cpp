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

#include "Input.hpp"

namespace mb
{
  void Input::initialize()
  {
    Input* _instance = Input::instance();

    _instance->_keyboard = new GLFWKeyboard();
    _instance->_mouse = new GLFWMouse();
  }
  void Input::destroy()
  {
    Input* _instance = Input::instance();
    delete _instance->_mouse;
    delete _instance->_keyboard;
    delete _instance;
  }
  mb::Keyboard* Input::Keyboard()
  {
    auto input = Input::instance();
    return input->_keyboard;
  }
  mb::Mouse* Input::Mouse()
  {
    auto input = Input::instance();
    return input->_mouse;
  }
  bool Input::isKeyPressed(Keyboard::Key key)
  {
    auto input = Input::instance();
    return input->_keyboard->keyPress(key);
  }
  bool Input::isKeyClicked(Keyboard::Key key)
  {
    auto input = Input::instance();
    return input->_keyboard->singleKeyPress(key);
  }
  bool Input::KeyReleased(Keyboard::Key key)
  {
    auto input = Input::instance();
    return input->_keyboard->keyRelease(key);
  }
  int Input::MouseX()
  {
    auto input = Input::instance();
    return input->_mouse->mouseX();
  }
  int Input::MouseY()
  {
    auto input = Input::instance();
    return input->_mouse->mouseY();
  }
  Input* Input::instance()
  {
    if (!Input::_instance)
    {
      Input::_instance = new mb::Input();
    }
    return Input::_instance;
  }
  int Input::PreviousMouseX()
  {
    auto input = Input::instance();
    return input->_mouse->previousMouseX();
  }
  int Input::PreviousMouseY()
  {
    auto input = Input::instance();
    return input->_mouse->previousMouseY();
  }
  int Input::MouseWheelX()
  {
    auto input = Input::instance();
    return input->_mouse->mouseWheelX();
  }
  int Input::MouseWheelY()
  {
    auto input = Input::instance();
    return input->_mouse->mouseWheelY();
  }
  int Input::DeltaX(int val)
  {
    auto input = Input::instance();
    return input->_mouse->deltaX(val);
  }
  int Input::DeltaY(int val)
  {
    auto input = Input::instance();
    return input->_mouse->deltaY(val);
  }
  bool Input::MouseButtonPress(MouseButton button)
  {
    auto input = Input::instance();
    return input->_mouse->buttonPress(button);
  }
  bool Input::MouseButtonSinglePress(MouseButton button)
  {
    auto input = Input::instance();
    return input->_mouse->singleButtonPress(button);
  }
  bool Input::MouseButtonRelease(MouseButton button)
  {
    auto input = Input::instance();
    return input->_mouse->buttonRelease(button);
  }
  void Input::update()
  {
    Input* _instance = Input::instance();
    _instance->_keyboard->update();
    _instance->_mouse->update();
  }
  Input* Input::_instance = nullptr;
}
