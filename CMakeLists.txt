project(cpp_training)
cmake_minimum_required(VERSION 3.5)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(SOURCES
    image_factory.cpp
    loader.cpp
    libpng_wrapper.cpp
    image.cpp
    )

foreach(_src ${SOURCES})
    list(APPEND SOURCES_OUT src/${_src})
endforeach()

add_library(algo ${SOURCES_OUT})
if (${CMAKE_VERSION} VERSION_LESS "3.8.0")
    set(CMAKE_CXX_FLAGS "${CMKAE_CXX_FLAGS} -std=c++17")
else()
    set_target_properties(algo PROPERTIES CXX_STANDARD 17)
endif()

add_executable(vr main.cpp)
target_link_libraries(vr algo)

add_subdirectory(test)
add_subdirectory(tools)
