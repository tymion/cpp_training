include(ExternalProject)
ExternalProject_Add(
    GTEST
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/gtest
    DOWNLOAD_COMMAND ""
    UPDATE_COMMAND ""
    INSTALL_COMMAND ""
    )
