source_group(\\ FILES CMakeLists.txt)

set( MB_PUBLIC_HEADERS
  Boundings/BoundingVolume.hpp
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
  Components/ScriptComponent.hpp


  Exceptions/Exception.hpp
  Exceptions/FileNotFoundException.hpp
  Exceptions/HasParentException.hpp
  Exceptions/RuntimeException.hpp


  Io/Input.hpp
  Io/Keyboard.hpp
  Io/Mouse.hpp
  Io/Window.hpp
  Io/os.hpp
  #Io/GLFWWindow2.hpp


  Maths/Clock.hpp
  Maths/Frustum.hpp
  Maths/Mathf.hpp
  Maths/Ray.hpp
  Maths/Rect.hpp


  Primitives/Primitive.hpp
  Primitives/CapsulePrimitive.hpp
  Primitives/CubePrimitive.hpp
  Primitives/PlanePrimitive.hpp
  Primitives/SpherePrimitive.hpp
  Primitives/TorusPrimitive.hpp


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
  Rendering/PipelineState.hpp
  Rendering/StandardMaterial.hpp
  Rendering/Texture.hpp


  Scenegraph/Camera.hpp
  Scenegraph/Geometry.hpp
  Scenegraph/Group.hpp
  Scenegraph/Light.hpp
  Scenegraph/LOD.hpp
  Scenegraph/Node.hpp
  Scenegraph/Switch.hpp


  State/ExampleStates.hpp
  State/StateMachine.hpp


  Systems/RenderSystem.hpp
  Systems/System.hpp
  Systems/UpdateSystem.hpp


  Utils/any.hpp
  Utils/CustomPingPong.hpp
  Utils/CustomPingPong.inl
  #Utils/Easing.hpp
  Utils/Log.hpp
  Utils/Macros.hpp
  Utils/MemoryUtils.hpp
  Utils/NonCopyable.hpp
  ##Utils/Params.hpp
  Utils/StringUtils.hpp


  Visitors/ChildrenCounterVisitor.hpp
  Visitors/DumpVisitor.hpp
  Visitors/FetchCameras.hpp
  Visitors/ComputeBatchQueue.hpp
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

  Includes.hpp




  OpenGL/Program.hpp
  OpenGL/ResourceShader.hpp
)

set( MB_HEADERS
)

set( MB_SOURCES
  Components/Component.cpp
  Components/CustomComponent.cpp
  Components/LambdaComponent.cpp
  Components/MaterialComponent.cpp
  Components/MeshRenderer.cpp
  Components/OtherComponent.cpp
  Components/ScriptComponent.cpp


  Io/Input.cpp
  Io/Keyboard.cpp
  Io/Mouse.cpp
  Io/Window.cpp
  #Io/GLFWWindow2.cpp


  Maths/Clock.cpp
  Maths/Frustum.cpp
  Maths/Mathf.cpp

  Primitives/Primitive.cpp
  Primitives/CapsulePrimitive.cpp
  Primitives/CubePrimitive.cpp
  Primitives/PlanePrimitive.cpp
  Primitives/SpherePrimitive.cpp
  Primitives/TorusPrimitive.cpp

  Rendering/ImageEffects/GreyImageEffect.cpp
  Rendering/ImageEffects/SepiaImageEffect.cpp

  Rendering/RenderPasses/OffscreenRenderingPass.cpp
  Rendering/RenderPasses/PostRenderingPass.cpp
  Rendering/RenderPasses/RenderingPass.cpp
  Rendering/RenderPasses/StandardRenderingPass.cpp
  #Rendering/RenderPasses/DeferredRenderingPass.cpp

  Rendering/BatchQueue.cpp
  Rendering/Material.cpp
  Rendering/Renderer.cpp


  Scenegraph/Camera.cpp
  Scenegraph/Geometry.cpp
  Scenegraph/Group.cpp
  Scenegraph/Light.cpp
  Scenegraph/LOD.cpp
  Scenegraph/Node.cpp
  Scenegraph/Switch.cpp


  State/StateMachine.cpp


  Systems/RenderSystem.cpp
  Systems/System.cpp
  Systems/UpdateSystem.cpp


  #Utils/Easing.cpp
  Utils/Log.cpp


  Visitors/ChildrenCounterVisitor.cpp
  Visitors/DumpVisitor.cpp
  Visitors/FetchCameras.cpp
  Visitors/ComputeBatchQueue.cpp
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




  OpenGL/Program.cpp
  OpenGL/ResourceShader.cpp
)

set( MB_LINK_LIBRARIES
  ${OPENGL_LIBRARIES}
  ${GLEW_LIBRARIES}
  ${FREEIMAGE_LIBRARIES}
  ${GLFW3_LIBRARIES}
)

common_library( mb )
