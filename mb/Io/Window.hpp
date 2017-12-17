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


#include <FreeImage.h>
#include "../Includes.hpp"

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

    // TODO: MOVE TO ANOTHER ZONE
    void saveToImage( const std::string& file )
    {
      BYTE* pixels = new BYTE[ 3 * _params.width * _params.height ];
      glReadPixels( 0, 0, _params.width, _params.height, GL_RGB, GL_UNSIGNED_BYTE, pixels );
      // Convert to FreeImage format & save to file
      FIBITMAP* image = FreeImage_ConvertFromRawBits( pixels, _params.width, 
        _params.height, 3 * _params.width, 24, 0x0000FF, 0xFF0000, 0x00FF00, false );
      FreeImage_Save( FIF_BMP, image, file.c_str( ), 0 ); // Free resources
      FreeImage_Unload( image );
      delete[ ] pixels;

    }
  protected:
    WindowParams _params;
  };
}

#endif /* __MB_WINDOW__ */
