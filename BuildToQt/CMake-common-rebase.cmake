if(NOT IS_DIRECTORY "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/CMake/common/.git")
  message(FATAL_ERROR "Can't update git external CMake/common: Not a git repository")
endif()
execute_process(COMMAND "/usr/bin/git" rev-parse --short HEAD
  OUTPUT_VARIABLE currentref OUTPUT_STRIP_TRAILING_WHITESPACE
  WORKING_DIRECTORY "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/CMake/common")
if(currentref STREQUAL dd94e50) # nothing to do
  return()
endif()

foreach(GIT_EXTERNAL_RESET_FILE )
  execute_process(
    COMMAND "/usr/bin/git" reset -q "${GIT_EXTERNAL_RESET_FILE}"
    ERROR_QUIET OUTPUT_QUIET
    WORKING_DIRECTORY "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/CMake/common")
  execute_process(
    COMMAND "/usr/bin/git" checkout -q -- ""
    ERROR_QUIET OUTPUT_QUIET
    WORKING_DIRECTORY "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/CMake/common")
endforeach()

execute_process(COMMAND "/usr/bin/git" fetch origin -q
  RESULT_VARIABLE nok ERROR_VARIABLE error
  WORKING_DIRECTORY "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/CMake/common")
if(nok)
  message(FATAL_ERROR "Fetch for CMake/common failed:
   ${error}")
endif()

execute_process(
  COMMAND "/usr/bin/git" checkout -q "dd94e50"
  RESULT_VARIABLE nok ERROR_VARIABLE error
  WORKING_DIRECTORY "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/CMake/common")
if(nok)
  message(FATAL_ERROR "git checkout dd94e50 in CMake/common failed: 
")
endif()
