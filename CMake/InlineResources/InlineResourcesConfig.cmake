cmake_minimum_required(VERSION 3.9)

find_package(PythonInterp 2.7)

get_filename_component(generate_inline_resource_cmake ${CMAKE_CURRENT_LIST_DIR}/GenerateInlineResource.cmake ABSOLUTE)
get_filename_component(generate_inline_resource_py ${CMAKE_CURRENT_LIST_DIR}/GenerateInlineResource.py ABSOLUTE)
get_filename_component(inline_resource_template ${CMAKE_CURRENT_LIST_DIR}/InlineResource.cpp.in ABSOLUTE)

function(inline_resource target resource_file)

    set(inline_resources_dir ${CMAKE_CURRENT_BINARY_DIR}/${target}_InlineResources)
    file(MAKE_DIRECTORY ${inline_resources_dir})

    get_filename_component(resource_filename ${resource_file} NAME)
    get_filename_component(resource_directory ${resource_file} DIRECTORY)
    get_filename_component(resource_file_absolute ${resource_file} ABSOLUTE)

    if(resource_directory)
        set(resource_name ${resource_directory}/${resource_filename})
    else(resource_directory)
        set(resource_name ${resource_filename})
    endif(resource_directory)

    set(config_extra_files ${generate_inline_resource_cmake} ${inline_resource_template})

    if(PYTHONINTERP_FOUND)
        add_custom_command(
                OUTPUT ${inline_resources_dir}/${resource_name}.cpp
                DEPENDS ${resource_file} ${config_extra_files}
                COMMAND
                    ${PYTHON_EXECUTABLE} ${generate_inline_resource_py}
                    ${CMAKE_CURRENT_BINARY_DIR}
                    ${target} ${resource_name} ${resource_file_absolute} ${inline_resource_template}
        )
    else(PYTHONINTERP_FOUND)
        add_custom_command(
                OUTPUT ${inline_resources_dir}/${resource_name}.cpp
                DEPENDS ${resource_file} ${config_extra_files}
                COMMAND
                    ${CMAKE_COMMAND} -P ${generate_inline_resource_cmake}
                    ${target} ${resource_name} ${resource_file_absolute} ${inline_resource_template}
        )
    endif(PYTHONINTERP_FOUND)

    target_sources(${target} PUBLIC ${inline_resources_dir}/${resource_name}.cpp)

endfunction(inline_resource)

function(inline_resources target)

    foreach(resource_file_pattern ${ARGN})
        file(GLOB resource_files RELATIVE ${CMAKE_CURRENT_LIST_DIR} ${resource_file_pattern})
        foreach(resource_file ${resource_files})
            inline_resource(${target} ${resource_file})
        endforeach(resource_file)
    endforeach(resource_file_pattern)

endfunction(inline_resources)

find_path(InlineResources_INCLUDE_DIR InlineResources.h)
find_library(InlineResources_LIBRARY InlineResources)

if(InlineResources_INCLUDE_DIR AND InlineResources_LIBRARY)
    set(InlineResources_FOUND TRUE)
else(InlineResources_INCLUDE_DIR AND InlineResources_LIBRARY)
    set(InlineResources_FOUND FALSE)
endif(InlineResources_INCLUDE_DIR AND InlineResources_LIBRARY)

if(InlineResources_FOUND)
    message("-- Found InlineResources: ${InlineResources_LIBRARY}")
endif(InlineResources_FOUND)
