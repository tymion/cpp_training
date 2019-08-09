project(cpp_training)
cmake_minimum_required(VERSION 3.5)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${ROOTFS}/include)
include_directories(${ROOTFS}/usr/local/include)

link_directories (${ROOTFS}/lib)
link_directories (${ROOTFS}/usr/local/lib)

set(CURR_PATH ENV{PATH})

set(ENV{PATH} "${CURR_PATH}:${ROOTFS_HOST}/bin")

add_subdirectory(libs)

set(SOURCES
    image.cpp
    image_factory.cpp
    image_allocator.cpp
    image_file_factory.cpp
    libpng_wrapper.cpp
    image_processor_factory.cpp
    image_processor.cpp
    double_linked_region_list.cpp
    #    pngfile.cpp
    #    srs_test.cpp
    #    similar_region_search.cpp
    #    srs_out_data.cpp
    #    region_factory.cpp
    config.cpp
    #    mask.cpp
    #    pixel_3x8.cpp
    #    pixel_4x8.cpp
    )

foreach(_src ${SOURCES})
    list(APPEND SOURCES_OUT src/${_src})
endforeach()

add_library(algo SHARED ${SOURCES_OUT})
target_link_libraries(algo png z)
add_dependencies(algo libpng_target)

add_library(algo_debug SHARED ${SOURCES_OUT})
target_link_libraries(algo_debug png z)
add_dependencies(algo_debug libpng_target)
target_compile_definitions(algo_debug PUBLIC DEBUG=1 DEBUG_ALLOCATION=1)

if(${CMAKE_VERSION} VERSION_LESS "3.8.0")
    set(CMAKE_CXX_FLAGS "${CMKAE_CXX_FLAGS} -std=c++17")
else()
    set_target_properties(algo PROPERTIES CXX_STANDARD 17)
    set_target_properties(algo_debug PROPERTIES CXX_STANDARD 17)
endif()

set(CMAKE_CXX_FLAGS "${CMKAE_CXX_FLAGS} -Wall -pedantic -Wextra")

add_executable(vr new_main.cpp)
target_link_libraries(vr algo)

add_executable(vr_debug new_main.cpp)
target_link_libraries(vr_debug algo_debug)

if (CROSS_COMPILE)
    add_dependencies(vr qemu_target)
    add_dependencies(vr_debug qemu_target)
endif ()

if(NOT ${CMAKE_VERSION} VERSION_LESS "3.8.0")
    set_target_properties(vr PROPERTIES CXX_STANDARD 17)
    set_target_properties(vr_debug PROPERTIES CXX_STANDARD 17)
endif()

include(GNUInstallDirs)

install(TARGETS algo algo_debug vr vr_debug
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    )

add_subdirectory(test)
add_subdirectory(tools)
