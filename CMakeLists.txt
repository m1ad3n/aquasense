cmake_minimum_required(VERSION 3.2)

set(OpenGL_GL_PREFERENCE "GLVND")

project(AquaSense)

add_executable(app)
add_executable(asopen)

if (UNIX)
	find_package(OpenGL REQUIRED)
	find_package(GLEW REQUIRED)
	find_package(glfw3 REQUIRED)
	find_package(glm REQUIRED)

	target_link_libraries(app glfw ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} m glm::glm)
endif (UNIX)

target_include_directories(app PUBLIC src)
target_include_directories(asopen PUBLIC src)

if (WIN32)
	target_include_directories(app PUBLIC include)
	target_link_directories(app PUBLIC bin)
	target_include_directories(asopen PUBLIC include)
	target_link_directories(asopen PUBLIC bin)

	target_link_libraries(app opengl32 glfw3 glfw3dll glew32 glew32s m freetype)
	target_link_libraries(asopen opencv_core490.dll opencv_video490.dll opencv_highgui490.dll opengl32 glfw3 glfw3dll glew32 glew32s m freetype )

endif (WIN32)

add_subdirectory(src)

set_property(TARGET app PROPERTY CMAKE_CXX_STANDARD 17)
set_property(TARGET app PROPERTY CMAKE_CXX_STANDARD_REQUIRED ON)