# Install script for directory: /home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "lib")
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libmb.so.1.0.2"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libmb.so.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libmb.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY MESSAGE_LAZY FILES
    "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/BuildToQt/lib/libmb.so.1.0.2"
    "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/BuildToQt/lib/libmb.so.1"
    "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/BuildToQt/lib/libmb.so"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libmb.so.1.0.2"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libmb.so.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libmb.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/BuildToQt/include/mb/api.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/BuildToQt/include/mb/mb.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/BuildToQt/include/mb/version.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Application.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Boundings" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Boundings/BoundingVolume.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Boundings" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Boundings/BoxBoundingVolume.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Boundings" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Boundings/SphereBoundingVolume.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Components" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Components/BillboardComponent.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Components" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Components/Component.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Components" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Components/FreeCameraComponent.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Components" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Components/LambdaComponent.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Components" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Components/MaterialComponent.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Components" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Components/MeshRenderer.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Components" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Components/RotateComponent.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Exceptions" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Exceptions/Exception.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Exceptions" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Exceptions/FileNotFoundException.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Exceptions" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Exceptions/HasParentException.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Exceptions" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Exceptions/RuntimeException.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Includes.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Io" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Io/GLFWWindow2.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Io" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Io/Input.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Io" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Io/Keyboard.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Io" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Io/Mouse.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Io" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Io/Window.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Io" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Io/os.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Layer.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Materials" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Materials/BasicMaterial.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Materials" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Materials/ColorMaterial.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Materials" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Materials/FlatColorMaterial.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Materials" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Materials/FontMaterial.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Materials" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Materials/NormalMaterial.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Materials" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Materials/PointMaterial.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Materials" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Materials/PostProcessMaterial.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Materials" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Materials/StandardMaterial.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Materials" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Materials/ToonGradientMaterial.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Materials" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Materials/ToonMaterial.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Materials" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Materials/UVMaterial.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Maths" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Maths/Clock.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Maths" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Maths/Color.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Maths" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Maths/Curves.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Maths" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Maths/Frustum.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Maths" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Maths/Interpolation.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Maths" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Maths/Mathf.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Maths" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Maths/Matrix3.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Maths" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Maths/Matrix4.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Maths" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Maths/Plane.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Maths" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Maths/Quaternion.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Maths" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Maths/Random.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Maths" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Maths/Ray.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Maths" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Maths/Rect.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Maths" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Maths/Sphere.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Maths" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Maths/Spherical.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Maths" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Maths/Transform.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Maths" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Maths/Vector2.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Maths" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Maths/Vector3.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Maths" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Maths/Vector4.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/OpenGL" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/OpenGL/OpenGLMapping.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/OpenGL" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/OpenGL/OpenGLRenderer.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/OpenGL" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/OpenGL/Program.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/OpenGL" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/OpenGL/ResourceShader.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Primitives" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Primitives/CapsulePrimitive.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Primitives" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Primitives/CubePrimitive.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Primitives" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Primitives/MeshPrimitive.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Primitives" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Primitives/PlanePrimitive.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Primitives" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Primitives/PointPrimitive.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Primitives" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Primitives/PolyhedronPrimitive.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Primitives" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Primitives/Primitive.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Primitives" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Primitives/SpherePrimitive.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Primitives" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Primitives/TorusPrimitive.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Rendering" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Rendering/BatchQueue.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Rendering/ImageEffects" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Rendering/ImageEffects/GreyImageEffect.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Rendering/ImageEffects" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Rendering/ImageEffects/ImageEffect.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Rendering/ImageEffects" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Rendering/ImageEffects/SepiaImageEffect.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Rendering" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Rendering/Material.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Rendering" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Rendering/PipelineState.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Rendering" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Rendering/RenderBuffer.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Rendering/RenderPasses" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Rendering/RenderPasses/OffscreenRenderingPass.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Rendering/RenderPasses" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Rendering/RenderPasses/PostRenderingPass.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Rendering/RenderPasses" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Rendering/RenderPasses/RenderingPass.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Rendering/RenderPasses" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Rendering/RenderPasses/StandardRenderingPass.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Rendering" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Rendering/Renderer.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Rendering" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Rendering/Texture.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Scenegraph" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Scenegraph/Camera.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Scenegraph" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Scenegraph/Geometry.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Scenegraph" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Scenegraph/Group.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Scenegraph" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Scenegraph/Light.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Scenegraph" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Scenegraph/LodNode.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Scenegraph" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Scenegraph/Node.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Scenegraph" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Scenegraph/Scene.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Scenegraph" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Scenegraph/Switch.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/State" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/State/StateMachine.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Utils" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Utils/CustomPingPong.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Utils" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Utils/CustomPingPong.inl")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Utils" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Utils/Easing.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Utils" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Utils/FileSystem.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Utils" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Utils/JobScheduler.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Utils" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Utils/Log.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Utils" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Utils/Macros.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Utils" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Utils/MemoryUtils.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Utils" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Utils/NonCopyable.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Utils" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Utils/ObjLoader.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Utils" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Utils/Settings.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Utils" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Utils/Singleton.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Utils" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Utils/StringUtils.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Utils" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Utils/any.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Visitors" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Visitors/ChildrenCounterVisitor.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Visitors" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Visitors/ComputeBatchQueue.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Visitors" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Visitors/DebugRenderVisitor.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Visitors" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Visitors/DumpVisitor.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Visitors" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Visitors/FetchCameras.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Visitors" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Visitors/FetchLights.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Visitors" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Visitors/FindNodes.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Visitors" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Visitors/LambdaVisitor.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Visitors" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Visitors/PickingVisitor.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Visitors" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Visitors/PrintNameVisitor.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Visitors" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Visitors/StartComponents.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Visitors" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Visitors/UpdateComponents.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Visitors" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Visitors/UpdateWorldState.hpp")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb/Visitors" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/mb/Visitors/Visitor.hpp")
endif()

