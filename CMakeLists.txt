cmake_minimum_required(VERSION 3.5.0)
project(dawn1 VERSION 0.1.0 LANGUAGES C CXX)


file(GLOB_RECURSE MAIN_SRC ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(dawn1 ${MAIN_SRC} main.cpp )

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set_target_properties(dawn1 PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    COMPILE_WARNING_AS_ERROR OFF
)
include_directories(${PROJECT_SOURCE_DIR}/include)
find_package(glfw3 REQUIRED)
find_package(fmt)
find_package(glm CONFIG REQUIRED)
find_package(Boost 1.84.0 COMPONENTS program_options REQUIRED)

add_subdirectory(glfw3webgpu)
if (MSVC)
    target_compile_options(dawn1 PRIVATE /W4)
else()
    target_compile_options(dawn1 PRIVATE -Wall -Wextra -pedantic)
endif()

add_subdirectory(webgpu)
target_copy_webgpu_binaries(dawn1)

add_custom_target(
    copyres ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/resources ${PROJECT_SOURCE_DIR}/bin/resources
)

add_subdirectory(imgui)

file(COPY ${PROJECT_SOURCE_DIR}/resources DESTINATION ${PROJECT_SOURCE_DIR}/bin)
target_link_libraries(dawn1 PRIVATE webgpu glfw glfw3webgpu Boost::program_options glm::glm imgui fmt::fmt)