CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
project(glhckscene)

add_subdirectory(lib)

include_directories(
  ${kazmath_SOURCE_DIR}/src
  ${glhck_SOURCE_DIR}/include
  ${GLFW_SOURCE_DIR}/include
  ${engineworks_SOURCE_DIR}/include
  ${qmlon_SOURCE_DIR}/include
)

file(GLOB SOURCES src/*.cpp src/ew/*.cpp src/util/*.cpp)
add_definitions(-DGLHCK_KAZMATH_FLOAT -DUSE_SINGLE_PRECISION)
list(APPEND CMAKE_CXX_FLAGS -std=c++0x)
add_executable(glhckscene ${SOURCES})

target_link_libraries(glhckscene engineworks glfw glhck qmlon ${GLFW_LIBRARIES})

file(COPY scene DESTINATION .)
file(COPY model DESTINATION .)
file(COPY img DESTINATION .)
