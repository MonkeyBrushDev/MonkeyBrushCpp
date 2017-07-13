include_directories(
  ${PROJECT_BINARY_DIR}/include
  ${PROJECT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/routes.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/routes.h)


set( MBDEMOMATERIALS_HEADERS
  others/MatCapMaterial.hpp
  others/AlienProceduralMaterial.hpp
  others/GraniteProceduralMaterial.hpp
  others/HatchingProceduralMaterial.hpp
  others/FogShader.hpp
)
set( MBDEMOMATERIALS_SOURCES demoMaterials.cpp )
set( MBDEMOMATERIALS_LINK_LIBRARIES
  mb
)
common_application( mbDemoMaterials )


set( MBDEMOMODELLOADER_HEADERS )
set( MBDEMOMODELLOADER_SOURCES demoModelLoader.cpp )
set( MBDEMOMODELLOADER_LINK_LIBRARIES
  mb
)
common_application( mbDemoModelLoader )


set( MBDEMOPLANETS_HEADERS )
set( MBDEMOPLANETS_SOURCES demoPlanets.cpp )
set( MBDEMOPLANETS_LINK_LIBRARIES
  mb
)
common_application( mbDemoPlanets )


set( MBDEMOEARTH_HEADERS )
set( MBDEMOEARTH_SOURCES demoEarth.cpp )
set( MBDEMOEARTH_LINK_LIBRARIES
  mb
)
common_application( mbDemoEarth )


set( MBDEMOFOG_HEADERS
  others/FogShader.hpp
)
set( MBDEMOFOG_SOURCES demoFog.cpp )
set( MBDEMOFOG_LINK_LIBRARIES
  mb
)
common_application( mbDemoFog )


set( MBDEMOMULTICUBES_HEADERS )
set( MBDEMOMULTICUBES_SOURCES demoMultiCubes.cpp )
set( MBDEMOMULTICUBES_LINK_LIBRARIES
  mb
)
common_application( mbDemoMultiCubes )


set( MBDEMONORMALMAPPING_HEADERS )
set( MBDEMONORMALMAPPING_SOURCES demoNormalMapping.cpp )
set( MBDEMONORMALMAPPING_LINK_LIBRARIES
  mb
)
common_application( mbDemoNormalMapping )


## TODO: FAIL set( MBDEMOBUTTERFLIES_HEADERS )
## TODO: FAIL set( MBDEMOBUTTERFLIES_SOURCES demoButterflies.cpp )
## TODO: FAIL set( MBDEMOBUTTERFLIES_LINK_LIBRARIES
## TODO: FAIL   mb
## TODO: FAIL )
## TODO: FAIL common_application( mbDemoButterflies )



set( MBDEMOPOSTPROCESS_HEADERS )
set( MBDEMOPOSTPROCESS_SOURCES demoPostProcess.cpp )
set( MBDEMOPOSTPROCESS_LINK_LIBRARIES
  mb
)
common_application( mbDemoPostProcess )



set( MBDEMOINTERPOLATIONS_HEADERS )
set( MBDEMOINTERPOLATIONS_SOURCES demoInterpolations.cpp )
set( MBDEMOINTERPOLATIONS_LINK_LIBRARIES
  mb
)
common_application( mbDemoInterpolations )




set( MBDEMOHEIGHTMAP_HEADERS )
set( MBDEMOHEIGHTMAP_SOURCES demoHeightMap.cpp )
set( MBDEMOHEIGHTMAP_LINK_LIBRARIES
  mb
)
common_application( mbDemoHeightMap )




set( MBDEMOSPHERICALHARMONICS_HEADERS )
set( MBDEMOSPHERICALHARMONICS_SOURCES demoSphericalHarmonics.cpp )
set( MBDEMOSPHERICALHARMONICS_LINK_LIBRARIES
  mb
)
common_application( mbDemoSphericalHarmonics )





set( MBDEMOPBR_HEADERS )
set( MBDEMOPBR_SOURCES demoPbr.cpp )
set( MBDEMOPBR_LINK_LIBRARIES
  mb
)
common_application( mbDemoPbr )





set( MBDEMOCLONE_HEADERS )
set( MBDEMOCLONE_SOURCES demoClone.cpp )
set( MBDEMOCLONE_LINK_LIBRARIES
  mb
)
common_application( mbDemoClone )

