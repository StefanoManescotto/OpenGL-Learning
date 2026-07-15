cmake_minimum_required(VERSION 3.20)
# Add 'C' to the languages here so CMake knows how to compile glad.c
project(GfxEngine VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/glad.c
        src/utilities.cpp
        include/utilities.h
        src/shader.cpp
        include/shader.h
        src/texture.cpp
        include/texture.h
        include/geometry.h
        src/camera.cpp
        include/camera.h
)

target_include_directories(${PROJECT_NAME} PRIVATE
        src
        include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        glfw
        GL
        ${CMAKE_DL_LIBS}
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
        SHADER_DIR="${CMAKE_SOURCE_DIR}/shaders/"
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
        RESOURCES_DIR="${CMAKE_SOURCE_DIR}/resources/"
)
