project(cpp_training)
cmake_minimum_required(VERSION 3.5)

include(FindPkgConfig)
if(NOT PKG_CONFIG_FOUND)
    message (FATAL_ERROR "pkg-config not found")
endif()

set(CMAKE_PREFIX_PATH ${ROOTFS})

pkg_check_modules (LIBPNG libpng16 REQUIRED)
include_directories (${LIBPNG_INCLUDE_DIRS})
link_directories (${LIBPNG_LIBRARY_DIRS})

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${ROOTFS}/include)
include_directories(${ROOTFS}/usr/local/include)

link_directories (${ROOTFS}/lib)
link_directories (${ROOTFS}/usr/local/lib)

set(SOURCES
    image_factory.cpp
    loader.cpp
    libpng_wrapper.cpp
    pngfile.cpp
    image.cpp
    srs_test.cpp
    similar_region_search.cpp
    srs_out_data.cpp
    region_factory.cpp
    config.cpp
    mask.cpp
    pixel_3x8.cpp
    pixel_4x8.cpp
    )

foreach(_src ${SOURCES})
    list(APPEND SOURCES_OUT src/${_src})
endforeach()

add_library(algo ${SOURCES_OUT})
target_link_libraries(algo ${LIBPNG_LIBRARIES})
if(${CMAKE_VERSION} VERSION_LESS "3.8.0")
    set(CMAKE_CXX_FLAGS "${CMKAE_CXX_FLAGS} -std=c++17")
else()
    set_target_properties(algo PROPERTIES CXX_STANDARD 17)
endif()

add_executable(vr main.cpp)
target_link_libraries(vr algo)

add_subdirectory(libs)
add_subdirectory(test)
add_subdirectory(tools)
