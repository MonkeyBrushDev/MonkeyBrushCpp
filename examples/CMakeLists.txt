include_directories(
  ${PROJECT_BINARY_DIR}/include
  ${PROJECT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/routes.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/routes.h)

## set( MBEXAMPLE01_HEADERS )
## set( MBEXAMPLE01_SOURCES example01.cpp )
## set( MBEXAMPLE01_LINK_LIBRARIES
##   mb
## )
## common_application( mbExample01 )


## set( MBEXAMPLECAR_HEADERS )
## set( MBEXAMPLECAR_SOURCES exampleCar.cpp )
## set( MBEXAMPLECAR_LINK_LIBRARIES
##   mb
## )
## common_application( mbExampleCar )


## set( MBEXAMPLE02_HEADERS )
## set( MBEXAMPLE02_SOURCES example02.cpp )
## set( MBEXAMPLE02_LINK_LIBRARIES
##   mb
## )
## common_application( mbExample02 )


## set( MBEXAMPLEGROUP_HEADERS )
## set( MBEXAMPLEGROUP_SOURCES exampleGroup.cpp )
## set( MBEXAMPLEGROUP_LINK_LIBRARIES
##   mb
## )
## common_application( mbExampleGroup )


## set( MBEXAMPLEPOSTPROCESS_HEADERS )
## set( MBEXAMPLEPOSTPROCESS_SOURCES examplePostProcess.cpp )
## set( MBEXAMPLEPOSTPROCESS_LINK_LIBRARIES
##   mb
## )
## common_application( mbExamplePostProcess )


## set( MBEXAMPLEOFFSCREEN_HEADERS )
## set( MBEXAMPLEOFFSCREEN_SOURCES exampleOffScreen.cpp )
## set( MBEXAMPLEOFFSCREEN_LINK_LIBRARIES
##   mb
## )
## common_application( mbExampleOffScreen )


## set( MBEXAMPLERAWTRIANGLE_HEADERS )
## set( MBEXAMPLERAWTRIANGLE_SOURCES exampleRawTriangle.cpp )
## set( MBEXAMPLERAWTRIANGLE_LINK_LIBRARIES
##   mb
## )
## common_application( mbExampleRawTriangle )


## set( MBEXAMPLERAWCUBE_HEADERS )
## set( MBEXAMPLERAWCUBE_SOURCES exampleRawCube.cpp )
## set( MBEXAMPLERAWCUBE_LINK_LIBRARIES
##   mb
## )
## common_application( mbExampleRawCube )




## set( MBEXAMPLERAWCUBECAMERA_HEADERS )
## set( MBEXAMPLERAWCUBECAMERA_SOURCES exampleRawCubeCamera.cpp )
## set( MBEXAMPLERAWCUBECAMERA_LINK_LIBRARIES
##   mb
## )
## common_application( mbExampleRawCubeCamera )





set( MBEXAMPLEWINDOW_HEADERS )
set( MBEXAMPLEWINDOW_SOURCES exampleWindow.cpp )
set( MBEXAMPLEWINDOW_LINK_LIBRARIES
  mb
)
common_application( mbExampleWindow )




set( MBTESTS_HEADERS )
set( MBTESTS_SOURCES tests.cpp )
set( MBTESTS_LINK_LIBRARIES
  mb
)
common_application( mbTests )



set( MBEXAMPLEPLANETS_HEADERS )
set( MBEXAMPLEPLANETS_SOURCES examplePlanets.cpp )
set( MBEXAMPLEPLANETS_LINK_LIBRARIES
  mb
)
common_application( mbExamplePlanets )


set( MBEXAMPLETHREE1_HEADERS )
set( MBEXAMPLETHREE1_SOURCES exampleThree1.cpp )
set( MBEXAMPLETHREE1_LINK_LIBRARIES
  mb
)
common_application( mbExampleThree1 )



set( MBEXAMPLEFOG_HEADERS )
set( MBEXAMPLEFOG_SOURCES exampleFog.cpp )
set( MBEXAMPLEFOG_LINK_LIBRARIES
  mb
)
common_application( mbExampleFog )



set( MBEXAMPLEMODELLOADER_HEADERS )
set( MBEXAMPLEMODELLOADER_SOURCES exampleModelLoader.cpp )
set( MBEXAMPLEMODELLOADER_LINK_LIBRARIES
  mb
)
common_application( mbExampleModelLoader )


##set( MBEXAMPLETRIANGLE_HEADERS )
##set( MBEXAMPLETRIANGLE_SOURCES exampleTriangle.cpp )
##set( MBEXAMPLETRIANGLE_LINK_LIBRARIES
##  mb
##)
##common_application( mbExampleTriangle )


set( MBEXAMPLEDEMO_HEADERS
  AlienProceduralMaterial.hpp
  MatCapMaterial.hpp
  GraniteProceduralMaterial.hpp
  TurbulenceProceduralMaterial.hpp
  HatchingProceduralMaterial.hpp
  IceMaterial.hpp
)
set( MBEXAMPLEDEMO_HEADERS MatCapMaterial.hpp )
set( MBEXAMPLEDEMO_SOURCES exampleDemo.cpp )
set( MBEXAMPLEDEMO_LINK_LIBRARIES
  mb
)
common_application( mbExampleDemo )

set( MBEXAMPLEEARTH_HEADERS )
set( MBEXAMPLEEARTH_SOURCES exampleEarth.cpp )
set( MBEXAMPLEEARTH_LINK_LIBRARIES
  mb
)
common_application( mbExampleEarth )

set( MBEXAMPLEBUTTERFLIES_HEADERS )
set( MBEXAMPLEBUTTERFLIES_SOURCES exampleButterflies.cpp )
set( MBEXAMPLEBUTTERFLIES_LINK_LIBRARIES
  mb
)
common_application( mbExampleButterflies )
