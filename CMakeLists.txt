cmake_minimum_required(VERSION 3.0)
project(AquaSense)

set(OpenGL_GL_PREFERENCE "GLVND")

add_executable(app)

if (UNIX)
	find_package(OpenGL REQUIRED)
	find_package(GLEW REQUIRED)
	find_package(glfw3 REQUIRED)
	find_package(glm REQUIRED)

	target_link_libraries(app glfw ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} m glm::glm)
endif (UNIX)

target_include_directories(app PUBLIC src)

if (WIN32)
	target_include_directories(app PUBLIC glew/include)
	target_include_directories(app PUBLIC glfw/include)
	target_include_directories(app PUBLIC glm)

	target_link_directories(app PUBLIC glew/lib/Release/x64)
	target_link_directories(app PUBLIC glfw/lib-mingw-w64)

	target_link_libraries(app opengl32 glfw3 glfw3dll glew32 glew32s m)
endif (WIN32)

add_subdirectory(src)

set_property(TARGET app PROPERTY CMAKE_CXX_STANDARD 11)
set_property(TARGET app PROPERTY CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(TARGET app PROPERTY CMAKE_EXPORT_COMPILE_COMMANDS ON)