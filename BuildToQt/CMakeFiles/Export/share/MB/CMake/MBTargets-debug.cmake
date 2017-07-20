#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "mb" for configuration "Debug"
set_property(TARGET mb APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(mb PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libmb.so.1.0.2"
  IMPORTED_SONAME_DEBUG "libmb.so.1"
  )

list(APPEND _IMPORT_CHECK_TARGETS mb )
list(APPEND _IMPORT_CHECK_FILES_FOR_mb "${_IMPORT_PREFIX}/lib/libmb.so.1.0.2" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
