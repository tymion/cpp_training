
set(TOOLS
    cnt_max.cpp
    generate_data.cpp
    start_point.cpp
    )

foreach(_tool ${TOOLS})
    get_filename_component(_tool_base ${_tool} NAME_WE)
    add_executable(${_tool_base} ${_tool})
    target_link_libraries(${_tool_base} algo)
endforeach()
