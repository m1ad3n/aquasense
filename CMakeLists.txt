cmake_minimum_required(VERSION 3.0)
project(AquaSense)

set(OpenGL_GL_PREFERENCE "GLVND")

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

add_executable(app)

target_link_libraries(app glfw ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} m glm::glm)
target_include_directories(app PUBLIC src)

set_property(TARGET app PROPERTY CMAKE_CXX_STANDARD 11)
set_property(TARGET app PROPERTY CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(TARGET app PROPERTY CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)
