include(ExternalProject)
ExternalProject_Add(
    gtest_target
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/gtest
    DOWNLOAD_COMMAND ""
    UPDATE_COMMAND ""
    CMAKE_ARGS ""
    INSTALL_COMMAND make DESTDIR=${ROOTFS} install
    )
