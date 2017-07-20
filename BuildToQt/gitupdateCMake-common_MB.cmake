
include("/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/CMake/GitExternal.cmake")
execute_process(COMMAND "/usr/bin/git" fetch origin -q
  WORKING_DIRECTORY "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/CMake/common")
execute_process(
  COMMAND "/usr/bin/git" show-ref --hash=7 refs/remotes/origin/master
  OUTPUT_VARIABLE newref OUTPUT_STRIP_TRAILING_WHITESPACE
  WORKING_DIRECTORY "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/CMake/common")
if(newref)
  file(APPEND /home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/.gitexternals "# CMake/common https://github.com/Eyescale/CMake.git ${newref}\n")
  git_external(CMake/common https://github.com/Eyescale/CMake.git ${newref})
else()
  file(APPEND /home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp/.gitexternals "# CMake/common https://github.com/Eyescale/CMake.git dd94e50
")
endif()