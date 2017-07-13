# Branch:
   execute_process(COMMAND "/usr/bin/git" branch 1.0
     RESULT_VARIABLE hadbranch ERROR_VARIABLE error
     WORKING_DIRECTORY /home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp)
   if(NOT hadbranch)
     execute_process(COMMAND "/usr/bin/git" push origin 1.0
      WORKING_DIRECTORY "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp")
   endif()
   set(TAG_BRANCH 1.0)

   # Create or move tag
   execute_process(
     COMMAND "/usr/bin/git" tag -f 1.0.2 
     COMMAND "/usr/bin/git" push --tags
     RESULT_VARIABLE notdone WORKING_DIRECTORY "/home/rjarillo/Documentos/Personal/ElMotorcico/MonkeyBrushCpp")
   if(notdone)
     message(FATAL_ERROR
        "Error creating tag 1.0.2 on branch ")
   endif()