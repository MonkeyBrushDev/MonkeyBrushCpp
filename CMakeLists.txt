cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(MB VERSION 1.0.1 )
set(MB_VERSION_ABI 1)

# Disable in source building
if( "${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}" )
    message( FATAL "no in source building allowed." )
endif()

list(APPEND CMAKE_MODULE_PATH
    ${PROJECT_SOURCE_DIR}/CMake
    ${CMAKE_SOURCE_DIR}/CMake/common)

# Default build type is Debug
if( NOT CMAKE_BUILD_TYPE )
    set( CMAKE_BUILD_TYPE Debug )
endif( NOT CMAKE_BUILD_TYPE )

if ( CMAKE_BUILD_TYPE MATCHES "Debug" )
    add_definitions( -DDEBUG )
endif( )

include(GitExternal)

set(MB_DESCRIPTION "mb")
set(COMMON_PROJECT_DOMAIN MonkeyBrushDev)

include(Common)

# Allow warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error")


option( MB_WITH_COMPUTE_SHADERS "enabling/disabling compute shaders" ON )
option( MB_WITH_GEOMETRY_SHADERS "enabling/disabling geometry shaders" ON )
option( MB_WITH_TESSELATION_SHADERS
  "enabling/disabling tesselation shaders" ON )
option( MB_WITH_SUBPROGRAMS "enabling/disabling subprograms" ON )
option( MB_WITH_OCC_QUERY "enabling/disabling occlusion query" ON )
option( MB_WITH_TRANSFORM_FEEDBACK "enabling/disabling transform feedback" ON )

if ( MB_WITH_COMPUTE_SHADERS )
  list(APPEND COMMON_FIND_PACKAGE_DEFINES MB_COMPUTE_SHADERS)
endif( )

if ( MB_WITH_GEOMETRY_SHADERS )
  list(APPEND COMMON_FIND_PACKAGE_DEFINES MB_GEOMETRY_SHADERS)
endif( )

if ( MB_WITH_TESSELATION_SHADERS )
  list(APPEND COMMON_FIND_PACKAGE_DEFINES MB_TESSELATION_SHADERS)
endif( )

if ( MB_WITH_SUBPROGRAMS )
  list(APPEND COMMON_FIND_PACKAGE_DEFINES MB_SUBPROGRAMS)
endif( )

if ( MB_WITH_OCC_QUERY )
  list(APPEND COMMON_FIND_PACKAGE_DEFINES MB_OCC_QUERY)
endif( )

if ( MB_WITH_TRANSFORM_FEEDBACK )
  list(APPEND COMMON_FIND_PACKAGE_DEFINES MB_TRANSFORM_FEEDBACK)
endif( )

common_find_package( OpenGL REQUIRED SYSTEM )
common_find_package( GLEW REQUIRED SYSTEM )
common_find_package( GLFW3 REQUIRED SYSTEM )
common_find_package( Boost COMPONENTS unit_test_framework )

list ( APPEND MB_DEPENDENT_LIBRARIES OpenGL GLEW GLFW3 )

common_find_package_post( )

add_subdirectory( mb )
#add_subdirectory( physics )
add_subdirectory( examples )

if(${Boost_FOUND})
  add_subdirectory(tests)
endif()

set(DOXYGEN_MAINPAGE_MD ${PROJECT_SOURCE_DIR}/README.md)
set(DOXYGEN_EXTRA_INPUT ${DOXYGEN_MAINPAGE_MD})
include(CPackConfig)
include(DoxygenRule)
