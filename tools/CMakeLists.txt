
set(TOOLS
    cnt_max.cpp
    #generate_data.cpp
    #    start_point.cpp
    pixel_operations.cpp
    )

foreach(_tool ${TOOLS})
    get_filename_component(_tool_base ${_tool} NAME_WE)
    add_executable(${_tool_base} ${_tool})
    #    target_link_libraries(${_tool_base} algo)

    install(TARGETS ${_tool_base}
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    )
endforeach()
