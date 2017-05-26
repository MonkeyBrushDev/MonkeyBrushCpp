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

#ifndef __MB_WINDOW__
#define __MB_WINDOW__

#include <mb/api.h>

namespace mb
{
  struct WindowParams
  {
    const char* title;
    int width;
    int height;
    bool displayFPS;
    bool displayMouse;
    bool debugWindowEvents;
    unsigned int minVersion;
    unsigned int maxVersion;
    bool resizable;
    unsigned int depthBufferBit;
    unsigned int multiSample;
    MB_API
    WindowParams(int width_, int height_);
  };

  class Window
  {
  public:
    Window(const WindowParams& params) : _params(params) {}
    virtual ~Window() {};
    virtual bool init() = 0;
    virtual bool isRunning() = 0;
    virtual void pollEvents() = 0;
    virtual void close() = 0;
    virtual void swapBuffers() = 0;
    virtual void setTitle(const char* title) = 0;

    virtual void* getWindow() = 0;
  protected:
    WindowParams _params;
  };
}

#endif /* __MB_WINDOW__ */
