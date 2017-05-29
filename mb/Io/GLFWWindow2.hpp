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

#ifndef __MB_GLFWWINDOW2__
#define __MB_GLFWWINDOW2__

#include <mb/api.h>
#include "../Includes.hpp"

#include "Window.hpp"

namespace mb
{
  class GLFWWindow2 : public Window
  {
  public:
    MB_API
    virtual void* getWindow();
    MB_API
    GLFWWindow2(const WindowParams& params);
    MB_API
    virtual ~GLFWWindow2();
    MB_API
    virtual void setTitle(const char* title);
    MB_API
    virtual bool init();
    MB_API
    virtual bool isRunning();
    MB_API
    virtual void pollEvents();
    MB_API
    virtual void close();
    MB_API
    virtual void swapBuffers();
  protected:
    GLFWwindow* _handle;
  };
}

#endif /* __MB_GLFWWINDOW2__ */
