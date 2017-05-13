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
