cmake_minimum_required(VERSION 3.0)
project(AquaSense)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(app)
target_link_libraries(app glfw ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})
target_include_directories(app PUBLIC src)

add_subdirectory(src)
