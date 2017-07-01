include_directories(
  ${PROJECT_BINARY_DIR}/include
  ${PROJECT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/routes.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/routes.h)


set( MBEXAMPLEMATERIALS_HEADERS
  others/MatCapMaterial.hpp
  others/AlienProceduralMaterial.hpp
  others/GraniteProceduralMaterial.hpp
  others/HatchingProceduralMaterial.hpp
)
set( MBEXAMPLEMATERIALS_SOURCES exampleMaterials.cpp )
set( MBEXAMPLEMATERIALS_LINK_LIBRARIES
  mb
)
common_application( mbExampleMaterials )


set( MBEXAMPLEMODELLOADER_HEADERS )
set( MBEXAMPLEMODELLOADER_SOURCES exampleModelLoader.cpp )
set( MBEXAMPLEMODELLOADER_LINK_LIBRARIES
  mb
)
common_application( mbExampleModelLoader )


set( MBEXAMPLEPLANETS_HEADERS )
set( MBEXAMPLEPLANETS_SOURCES examplePlanets.cpp )
set( MBEXAMPLEPLANETS_LINK_LIBRARIES
  mb
)
common_application( mbExamplePlanets )


set( MBEXAMPLEEARTH_HEADERS )
set( MBEXAMPLEEARTH_SOURCES exampleEarth.cpp )
set( MBEXAMPLEEARTH_LINK_LIBRARIES
  mb
)
common_application( mbExampleEarth )


##set( MBEXAMPLEDEMO_HEADERS )
##set( MBEXAMPLEDEMO_SOURCES exampleDemo.cpp )
##set( MBEXAMPLEDEMO_LINK_LIBRARIES
##  mb
##)
##common_application( mbExampleDemo )


set( MBEXAMPLEFOG_HEADERS )
set( MBEXAMPLEFOG_SOURCES exampleFog.cpp )
set( MBEXAMPLEFOG_LINK_LIBRARIES
  mb
)
common_application( mbExampleFog )


set( MBEXAMPLEMULTICUBES_HEADERS )
set( MBEXAMPLEMULTICUBES_SOURCES exampleMultiCubes.cpp )
set( MBEXAMPLEMULTICUBES_LINK_LIBRARIES
  mb
)
common_application( mbExampleMultiCubes )


set( MBEXAMPLENORMALMAPPING_HEADERS )
set( MBEXAMPLENORMALMAPPING_SOURCES exampleNormalMapping.cpp )
set( MBEXAMPLENORMALMAPPING_LINK_LIBRARIES
  mb
)
common_application( mbExampleNormalMapping )


## TODO: FAIL set( MBEXAMPLEBUTTERFLIES_HEADERS )
## TODO: FAIL set( MBEXAMPLEBUTTERFLIES_SOURCES exampleButterflies.cpp )
## TODO: FAIL set( MBEXAMPLEBUTTERFLIES_LINK_LIBRARIES
## TODO: FAIL   mb
## TODO: FAIL )
## TODO: FAIL common_application( mbExampleButterflies )
