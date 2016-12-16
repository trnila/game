cmake_minimum_required(VERSION 3.6)
project(projekt)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") # -Wall -Wextra -pedantic

find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(assimp REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARIES} ${OPENGL_LIBRARIES} ${ASSIMP_LIBRARIES} glfw)

#  make clean && find src -type f | sort
set(SOURCE_FILES

		src/Game.cpp
src/Game.h
src/Graphics/BindableResource.h
src/Graphics/CubeMap.cpp
src/Graphics/CubeMap.h
src/Graphics/FrameBuffer.cpp
src/Graphics/FrameBuffer.h
src/Graphics/FrameBufferHandler.cpp
src/Graphics/FrameBufferHandler.h
src/Graphics/Material.cpp
src/Graphics/Material.h
src/Graphics/Mesh.cpp
src/Graphics/Mesh.h
src/Graphics/Model.cpp
src/Graphics/Model.h
src/Graphics/Program.cpp
src/Graphics/Program.h
src/Graphics/RenderContext.h
src/Graphics/Shader.cpp
src/Graphics/Shader.h
src/Graphics/Skybox.cpp
src/Graphics/Skybox.h
src/Graphics/Texture.cpp
src/Graphics/Texture.h
src/Graphics/VAO.cpp
src/Graphics/VAO.h
src/Graphics/VBO.cpp
src/Graphics/VBO.h
src/Input/KeyListener.h
src/Input/MouseListener.h
src/Logic.cpp
src/Logic.h
src/main.cpp
src/ObjectFactory.cpp
src/ObjectFactory.h
src/Scene/Camera.cpp
src/Scene/Camera.h
src/Scene/CameraHandler.cpp
src/Scene/CameraHandler.h
src/Scene.cpp
src/Scene.h
src/Scene/Lights/BaseLight.cpp
src/Scene/Lights/BaseLight.h
src/Scene/Lights/DirectionalLight.cpp
src/Scene/Lights/DirectionalLight.h
src/Scene/Lights/PointLight.cpp
src/Scene/Lights/PointLight.h
src/Scene/Lights/SpotLight.cpp
src/Scene/Lights/SpotLight.h
src/Scene/Node.cpp
src/Scene/Node.h
src/Scene/NodeList.cpp
src/Scene/NodeList.h
src/Scene/Object.cpp
src/Scene/Object.h
src/ShadowRenderer.cpp
src/ShadowRenderer.h
src/State.cpp
src/State.h
src/States.h
src/stb_image.h
src/Terrain.cpp
src/Terrain.h
src/Transformable.cpp
src/Transformable.h
		src/Utils/Color.h
src/Utils/Formatter.cpp
src/Utils/Formatter.h
src/Utils/Image.cpp
src/Utils/Image.h
src/Utils/Observer.h
src/Utils/ResourceManager.h
src/Utils/Singleton.h
src/Utils/StreamLog.cpp
src/Utils/StreamLog.h
src/Utils/utils.cpp
src/Utils/utils.h
src/Window.cpp
src/Window.h
src/GeneratedTerrain.cpp


		src/Panel.cpp src/Panel.h src/Utils/Matrix.cpp src/Utils/Matrix.h src/Utils/factorial.h src/Utils/factorial.cpp src/Factory.cpp src/Factory.h)
add_executable(projekt ${SOURCE_FILES})
