cmake_minimum_required(VERSION 3.2)

set(OpenGL_GL_PREFERENCE "GLVND")

project(AquaSense)

add_executable(aquasense)

if (UNIX)
	find_package(OpenGL REQUIRED)
	find_package(GLEW REQUIRED)
	find_package(glfw3 REQUIRED)
	find_package(glm REQUIRED)

	target_link_libraries(aquasense glfw ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} m glm::glm)
endif (UNIX)

target_include_directories(aquasense PUBLIC src)

if (WIN32)
	target_include_directories(aquasense PUBLIC include)
	target_link_directories(aquasense PUBLIC bin)

	target_link_libraries(aquasense opengl32 glfw3 glfw3dll glew32 glew32s m)

endif (WIN32)

add_subdirectory(src)

set_property(TARGET aquasense PROPERTY CMAKE_CXX_STANDARD 17)
set_property(TARGET aquasense PROPERTY CMAKE_CXX_STANDARD_REQUIRED ON)