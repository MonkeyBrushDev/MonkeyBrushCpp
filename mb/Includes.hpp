#ifndef __MB_INCLUDES__
#define __MB_INCLUDES__

#include <iostream>
#include "Utils/Log.hpp"

#ifndef SKIP_GLEW_INCLUDE
  #include <GL/glew.h>
#endif

#define SKIP_GLEW_INCLUDE 1

#ifdef Darwin
  #include <OpenGL/gl.h>
#else
  #include <GL/gl.h>
#endif

#include <GLFW/glfw3.h>

#endif /* __MB_INCLUDES__ */
