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
