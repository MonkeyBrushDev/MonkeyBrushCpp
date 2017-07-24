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


set( MBDEMOBUTTERFLIES_HEADERS )
set( MBDEMOBUTTERFLIES_SOURCES demoButterflies.cpp )
set( MBDEMOBUTTERFLIES_LINK_LIBRARIES
  mb
)
common_application( mbDemoButterflies )

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




set( MBDEMOCOMPUTESHADER_HEADERS )
set( MBDEMOCOMPUTESHADER_SOURCES demoComputeShader.cpp )
set( MBDEMOCOMPUTESHADER_LINK_LIBRARIES
  mb
)
common_application( mbDemoComputeShader )



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



set( MBDEMOS_HEADERS )
set( MBDEMOS_SOURCES demos.cpp )
set( MBDEMOS_LINK_LIBRARIES
  mb
)
common_application( mbDemos )


set( MBDEMOEXPLOSION_HEADERS )
set( MBDEMOEXPLOSION_SOURCES demoExplosion.cpp )
set( MBDEMOEXPLOSION_LINK_LIBRARIES
  mb
)
common_application( mbDemoExplosion )





set( MBDEMOSWAPTEXTURE_HEADERS )
set( MBDEMOSWAPTEXTURE_SOURCES demoSwapTexture.cpp )
set( MBDEMOSWAPTEXTURE_LINK_LIBRARIES
  mb
)
common_application( mbDemoSwapTexture )



set( MBDEMOBROWNIAN_HEADERS )
set( MBDEMOBROWNIAN_SOURCES demoBrownian.cpp )
set( MBDEMOBROWNIAN_LINK_LIBRARIES
  mb
)
common_application( mbDemoBrownian )




set( MBDEMOBLENDING_HEADERS )
set( MBDEMOBLENDING_SOURCES demoBlending.cpp )
set( MBDEMOBLENDING_LINK_LIBRARIES
  mb
)
common_application( mbDemoBlending )



set( MBDEMOWAYPOINTS_HEADERS )
set( MBDEMOWAYPOINTS_SOURCES demoWaypoints.cpp )
set( MBDEMOWAYPOINTS_LINK_LIBRARIES
  mb
)
common_application( mbDemoWaypoints )


set( MBDEMOGRASS_HEADERS )
set( MBDEMOGRASS_SOURCES demoGrass.cpp )
set( MBDEMOGRASS_LINK_LIBRARIES
  mb
)
common_application( mbDemoGrass )



set( MBDEMOMESHNORMALS_HEADERS )
set( MBDEMOMESHNORMALS_SOURCES demoMeshNormals.cpp )
set( MBDEMOMESHNORMALS_LINK_LIBRARIES
  mb
)
common_application( mbDemoMeshNormals )


set( MBDEMOTTF_HEADERS )
set( MBDEMOTTF_SOURCES demoTTF.cpp )
set( MBDEMOTTF_LINK_LIBRARIES
  mb
)
common_application( mbDemoTTF )



set( MBDEMOGEOMETRYSHADER_HEADERS )
set( MBDEMOGEOMETRYSHADER_SOURCES demoGeometryShader.cpp )
set( MBDEMOGEOMETRYSHADER_LINK_LIBRARIES
  mb
)
common_application( mbDemoGeometryShader )



set( MBDEMOSSBO_HEADERS )
set( MBDEMOSSBO_SOURCES demoSSbo.cpp )
set( MBDEMOSSBO_LINK_LIBRARIES
  mb
)
common_application( mbDemoSSbo )



set( MBDEMOVERTEXDISPLACEMENT_HEADERS )
set( MBDEMOVERTEXDISPLACEMENT_SOURCES demoVertexDisplacement.cpp )
set( MBDEMOVERTEXDISPLACEMENT_LINK_LIBRARIES
  mb
)
common_application( mbDemoVertexDisplacement )




set( MBDEMO3DTEXTURE_HEADERS )
set( MBDEMO3DTEXTURE_SOURCES demo3DTexture.cpp )
set( MBDEMO3DTEXTURE_LINK_LIBRARIES
  mb
)
common_application( mbDemo3DTexture )




set( MBDEMONORMALMATERIAL_HEADERS )
set( MBDEMONORMALMATERIAL_SOURCES demoNormalMaterial.cpp )
set( MBDEMONORMALMATERIAL_LINK_LIBRARIES
  mb
)
common_application( mbDemoNormalMaterial )
