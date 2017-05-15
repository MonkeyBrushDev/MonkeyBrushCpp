#ifndef __MB_GLFWWINDOW2__
#define __MB_GLFWWINDOW2__

#include <mb/api.h>

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
