set(TEST_SOURCES
    main.cpp
    algorithms_suite.cpp
    #    png_suite.cpp
    #integration_test_suite.cpp
    mask_suite.cpp
    #region_factory_suite.cpp
    configuration_suite.cpp
    libpng_suite.cpp
    pixel_suite.cpp
    region_suite.cpp
    )

add_executable(algo_test ${TEST_SOURCES})
add_dependencies(algo_test gtest_target)
target_link_libraries(algo_test algo gtest pthread)
if (CROSS_COMPILE)
    add_dependencies(algo_test qemu_target)
endif ()

install(TARGETS algo_test
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    )
