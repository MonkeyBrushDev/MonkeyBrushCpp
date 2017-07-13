# Install script for directory: /home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp

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

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/MB/CMake" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/BuildToQt/options.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/BuildToQt/include/mb/defines.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mb" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/BuildToQt/include/mb/definesLinux.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/MB/CMake" TYPE FILE MESSAGE_LAZY FILES
    "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/BuildToQt/MBConfig.cmake"
    "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/BuildToQt/MBConfigVersion.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/MB/CMake/MBTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/MB/CMake/MBTargets.cmake"
         "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/BuildToQt/CMakeFiles/Export/share/MB/CMake/MBTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/MB/CMake/MBTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/MB/CMake/MBTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/MB/CMake" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/BuildToQt/CMakeFiles/Export/share/MB/CMake/MBTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/MB/CMake" TYPE FILE MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/BuildToQt/CMakeFiles/Export/share/MB/CMake/MBTargets-debug.cmake")
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "doc")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/MB/doc/API" TYPE DIRECTORY MESSAGE_LAZY FILES "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/BuildToQt/doc/html")
  endif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/BuildToQt/mb/cmake_install.cmake")
  include("/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/BuildToQt/examples/cmake_install.cmake")
  include("/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/BuildToQt/tests/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/BuildToQt/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
