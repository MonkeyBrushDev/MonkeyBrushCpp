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
    this->minVersion = 3;
    this->maxVersion = 3;
    this->resizable = true;
    this->depthBufferBit = 24;
    this->multiSample = 4;
  }
}
