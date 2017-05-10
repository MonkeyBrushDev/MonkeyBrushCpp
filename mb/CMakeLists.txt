source_group(\\ FILES CMakeLists.txt)

set( MB_PUBLIC_HEADERS
  ##Boundings/BoundingVolume.hpp
  ##Boundings/BoxBoundingVolume.hpp
  ##Boundings/PlaneBoundingVolume.hpp
  ##Boundings/SphereBoundingVolume.hpp

  Components/Component.hpp
  Components/CustomComponent.hpp
  Components/LambdaComponent.hpp
  Components/MaterialComponent.hpp
  Components/MeshRenderer.hpp
  Components/OrbitCamera.hpp
  Components/OtherComponent.hpp

  Maths/Clock.hpp
  Maths/Frustum.hpp
  Maths/Ray.hpp

  Primitives/Primitive.hpp

  #Rendering/ImageEffects/BlurImageEffect.hpp
  Rendering/ImageEffects/GreyImageEffect.hpp
  Rendering/ImageEffects/ImageEffect.hpp
  Rendering/ImageEffects/SepiaImageEffect.hpp

  Rendering/RenderPasses/OffscreenRenderingPass.hpp
  Rendering/RenderPasses/PostRenderingPass.hpp
  Rendering/RenderPasses/RenderingPass.hpp
  Rendering/RenderPasses/StandardRenderingPass.hpp
  #Rendering/RenderPasses/DeferredRenderingPass.hpp

  Rendering/BatchQueue.hpp
  Rendering/Material.hpp
  Rendering/Renderer.hpp

  Scenegraph/Camera.hpp
  Scenegraph/Geometry.hpp
  Scenegraph/Group.hpp
  Scenegraph/Light.hpp
  Scenegraph/Node.hpp
  Scenegraph/Switch.hpp

  Systems/RenderSystem.hpp
  Systems/System.hpp
  Systems/UpdateSystem.hpp

  Utils/Macros.hpp
  ##Utils/Params.hpp


  Visitors/ChildrenCounterVisitor.hpp
  Visitors/DumpVisitor.hpp
  Visitors/FetchCameras.hpp
  Visitors/FetchGeometry.hpp
  Visitors/FetchLights.hpp
  Visitors/FindNodes.hpp
  Visitors/LambdaVisitor.hpp
  Visitors/PickingVisitor.hpp
  Visitors/PrintNameVisitor.hpp
  Visitors/StartComponents.hpp
  Visitors/UpdateComponents.hpp
  Visitors/UpdateWorldState.hpp
  Visitors/Visitor.hpp

  App.hpp
  Layer.hpp
  Scene.hpp
)

set( MB_HEADERS
)

set( MB_SOURCES
  Components/Component.cpp
  Components/CustomComponent.cpp
  Components/MaterialComponent.cpp
  Components/MeshRenderer.cpp
  Components/OtherComponent.cpp

  Maths/Clock.cpp
  Maths/Frustum.cpp

  Rendering/ImageEffects/GreyImageEffect.cpp
  Rendering/ImageEffects/SepiaImageEffect.cpp

  Rendering/RenderPasses/OffscreenRenderingPass.cpp
  Rendering/RenderPasses/PostRenderingPass.cpp
  Rendering/RenderPasses/RenderingPass.cpp
  Rendering/RenderPasses/StandardRenderingPass.cpp
  #Rendering/RenderPasses/DeferredRenderingPass.cpp

  Rendering/BatchQueue.cpp
  Rendering/Renderer.cpp

  Scenegraph/Camera.cpp
  Scenegraph/Geometry.cpp
  Scenegraph/Group.cpp
  Scenegraph/Light.cpp
  Scenegraph/Node.cpp
  Scenegraph/Switch.cpp

  Systems/RenderSystem.cpp
  Systems/System.cpp
  Systems/UpdateSystem.cpp


  Visitors/ChildrenCounterVisitor.cpp
  Visitors/DumpVisitor.cpp
  Visitors/FetchCameras.cpp
  Visitors/FetchGeometry.cpp
  Visitors/FetchLights.cpp
  Visitors/FindNodes.cpp
  Visitors/LambdaVisitor.cpp
  Visitors/PickingVisitor.cpp
  Visitors/PrintNameVisitor.cpp
  Visitors/StartComponents.cpp
  Visitors/UpdateComponents.cpp
  Visitors/UpdateWorldState.cpp
  Visitors/Visitor.cpp

  App.cpp
  Layer.cpp
)

set( MB_LINK_LIBRARIES
)

common_library( mb )
