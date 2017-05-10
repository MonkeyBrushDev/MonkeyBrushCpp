include_directories(
  ${PROJECT_BINARY_DIR}/include
  ${PROJECT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
)

set( MBEXAMPLE01_HEADERS )
set( MBEXAMPLE01_SOURCES example01.cpp )
set( MBEXAMPLE01_LINK_LIBRARIES
  mb
)
common_application( mbExample01 )


set( MBEXAMPLECAR_HEADERS )
set( MBEXAMPLECAR_SOURCES exampleCar.cpp )
set( MBEXAMPLECAR_LINK_LIBRARIES
  mb
)
common_application( mbExampleCar )


set( MBEXAMPLE02_HEADERS )
set( MBEXAMPLE02_SOURCES example02.cpp )
set( MBEXAMPLE02_LINK_LIBRARIES
  mb
)
common_application( mbExample02 )


set( MBEXAMPLEGROUP_HEADERS )
set( MBEXAMPLEGROUP_SOURCES exampleGroup.cpp )
set( MBEXAMPLEGROUP_LINK_LIBRARIES
  mb
)
common_application( mbExampleGroup )


set( MBTESTS_HEADERS )
set( MBTESTS_SOURCES tests.cpp )
set( MBTESTS_LINK_LIBRARIES
  mb
)
common_application( mbTests )


set( MBEXAMPLEPOSTPROCESS_HEADERS )
set( MBEXAMPLEPOSTPROCESS_SOURCES examplePostProcess.cpp )
set( MBEXAMPLEPOSTPROCESS_LINK_LIBRARIES
  mb
)
common_application( mbExamplePostProcess )


set( MBEXAMPLEOFFSCREEN_HEADERS )
set( MBEXAMPLEOFFSCREEN_SOURCES exampleOffScreen.cpp )
set( MBEXAMPLEOFFSCREEN_LINK_LIBRARIES
  mb
)
common_application( mbExampleOffScreen )

