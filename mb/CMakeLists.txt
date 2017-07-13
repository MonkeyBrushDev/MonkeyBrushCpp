source_group(\\ FILES CMakeLists.txt)

set( MB_PUBLIC_HEADERS
  Boundings/BoundingVolume.hpp
  Boundings/BoxBoundingVolume.hpp
  ##Boundings/PlaneBoundingVolume.hpp
  Boundings/SphereBoundingVolume.hpp

  Components/Component.hpp
  Components/LambdaComponent.hpp
  Components/MaterialComponent.hpp
  Components/MeshRenderer.hpp
  Components/RotateComponent.hpp
  Components/FreeCameraComponent.hpp
  Components/BillboardComponent.hpp


  Exceptions/Exception.hpp
  Exceptions/FileNotFoundException.hpp
  Exceptions/HasParentException.hpp
  Exceptions/RuntimeException.hpp


  Io/Input.hpp
  Io/Keyboard.hpp
  Io/Mouse.hpp
  Io/Window.hpp
  Io/os.hpp
  Io/GLFWWindow2.hpp


  Maths/Color.hpp
  Maths/Clock.hpp
  Maths/Frustum.hpp
  Maths/Mathf.hpp
  Maths/Ray.hpp
  Maths/Matrix3.hpp
  Maths/Matrix4.hpp
  Maths/Rect.hpp
  Maths/Quaternion.hpp
  Maths/Vector2.hpp
  Maths/Vector3.hpp
  Maths/Vector4.hpp
  Maths/Transform.hpp
  Maths/Spherical.hpp
  Maths/Random.hpp

  Maths/Curves.hpp
  Maths/Interpolation.hpp


  Maths/Plane.hpp
  Maths/Sphere.hpp
  Primitives/Primitive.hpp
  Primitives/CapsulePrimitive.hpp
  Primitives/CubePrimitive.hpp
  Primitives/PlanePrimitive.hpp
  Primitives/SpherePrimitive.hpp
  Primitives/TorusPrimitive.hpp
  Primitives/MeshPrimitive.hpp
  Primitives/PolyhedronPrimitive.hpp
  Primitives/PointPrimitive.hpp


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
  Rendering/Texture.hpp
  #Rendering/FramebufferObject.hpp
  #Rendering/RenderTarget.hpp
  Rendering/RenderBuffer.hpp


  Scenegraph/Camera.hpp
  Scenegraph/Geometry.hpp
  Scenegraph/Group.hpp
  Scenegraph/Light.hpp
  #Scenegraph/LOD.hpp
  Scenegraph/LodNode.hpp
  Scenegraph/Node.hpp
  Scenegraph/Switch.hpp
  Scenegraph/Scene.hpp


  State/StateMachine.hpp


##Systems/RenderSystem.hpp
##Systems/System.hpp
##Systems/UpdateSystem.hpp


  Utils/any.hpp
  Utils/CustomPingPong.hpp
  Utils/CustomPingPong.inl
  Utils/Easing.hpp
  Utils/Log.hpp
  Utils/Macros.hpp
  Utils/MemoryUtils.hpp
  Utils/NonCopyable.hpp
  Utils/Settings.hpp
  Utils/Singleton.hpp
  Utils/StringUtils.hpp


  Visitors/ChildrenCounterVisitor.hpp
  Visitors/DebugRenderVisitor.hpp
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

  Application.hpp
  Layer.hpp

  Includes.hpp


  Utils/FileSystem.hpp


  OpenGL/Program.hpp
  OpenGL/ResourceShader.hpp
  OpenGL/OpenGLRenderer.hpp

  Materials/StandardMaterial.hpp
  Materials/BasicMaterial.hpp
  Materials/ColorMaterial.hpp
  Materials/FontMaterial.hpp
  Materials/NormalMaterial.hpp
  Materials/PointMaterial.hpp
  Materials/ToonMaterial.hpp
  Materials/ToonGradientMaterial.hpp
  Materials/PostProcessMaterial.hpp
  Materials/UVMaterial.hpp
  Materials/FlatColorMaterial.hpp

  Utils/ObjLoader.hpp

  Utils/JobScheduler.hpp

  OpenGL/OpenGLMapping.hpp
  OpenGL/ComputeShader.hpp
)

set( MB_HEADERS
)

set( MB_SOURCES
  OpenGL/OpenGLRenderer.cpp


  Boundings/BoxBoundingVolume.cpp
  Boundings/SphereBoundingVolume.cpp



  Components/Component.cpp
  Components/LambdaComponent.cpp
  Components/MaterialComponent.cpp
  Components/MeshRenderer.cpp
  Components/RotateComponent.cpp
  Components/FreeCameraComponent.cpp
  Components/BillboardComponent.cpp


  Io/Input.cpp
  Io/Keyboard.cpp
  Io/Mouse.cpp
  Io/Window.cpp
  Io/GLFWWindow2.cpp


  Maths/Color.cpp
  Maths/Clock.cpp
  Maths/Frustum.cpp
  Maths/Matrix4.cpp
  Maths/Mathf.cpp
  Maths/Ray.cpp
  Maths/Quaternion.cpp
  Maths/Vector3.cpp
  Maths/Spherical.cpp
  Maths/Random.cpp

  Maths/Curves.cpp
  Maths/Interpolation.cpp

  Primitives/Primitive.cpp
  Primitives/CapsulePrimitive.cpp
  Primitives/CubePrimitive.cpp
  Primitives/PlanePrimitive.cpp
  Primitives/SpherePrimitive.cpp
  Primitives/TorusPrimitive.cpp
  Primitives/MeshPrimitive.cpp
  Primitives/PolyhedronPrimitive.cpp
  Primitives/PointPrimitive.cpp

  Rendering/ImageEffects/ImageEffect.cpp
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
  #Rendering/FramebufferObject.cpp
  Rendering/Texture.cpp
  Rendering/RenderBuffer.cpp


  Scenegraph/Camera.cpp
  Scenegraph/Geometry.cpp
  Scenegraph/Group.cpp
  Scenegraph/Light.cpp
  #Scenegraph/LOD.cpp
  Scenegraph/LodNode.cpp
  Scenegraph/Node.cpp
  Scenegraph/Switch.cpp
  Scenegraph/Scene.cpp


  State/StateMachine.cpp


##Systems/RenderSystem.cpp
##Systems/System.cpp
##Systems/UpdateSystem.cpp


  Utils/Easing.cpp
  Utils/Log.cpp


  Visitors/ChildrenCounterVisitor.cpp
  Visitors/DebugRenderVisitor.cpp
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


  Application.cpp
  Layer.cpp




  OpenGL/Program.cpp
  OpenGL/ResourceShader.cpp


  Materials/StandardMaterial.cpp
  Materials/BasicMaterial.cpp
  Materials/ColorMaterial.cpp
  Materials/FontMaterial.cpp
  Materials/NormalMaterial.cpp
  Materials/PointMaterial.cpp
  Materials/ToonMaterial.cpp
  Materials/ToonGradientMaterial.cpp
  Materials/PostProcessMaterial.cpp
  Materials/UVMaterial.cpp
  Materials/FlatColorMaterial.cpp

  Utils/JobScheduler.cpp

  OpenGL/OpenGLMapping.cpp
  OpenGL/ComputeShader.cpp
)

set( MB_LINK_LIBRARIES
  ${OPENGL_LIBRARIES}
  ${GLEW_LIBRARIES}
  ${FREEIMAGE_LIBRARIES}
  ${GLFW3_LIBRARIES}
  ${GLM_LIBRARIES}
)

common_library( mb )
