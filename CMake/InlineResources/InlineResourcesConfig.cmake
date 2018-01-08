cmake_minimum_required(VERSION 3.9)

get_filename_component(generate_inline_resource ${CMAKE_CURRENT_LIST_DIR}/GenerateInlineResource.cmake ABSOLUTE)
get_filename_component(inline_resource_template ${CMAKE_CURRENT_LIST_DIR}/InlineResource.cpp.in ABSOLUTE)

function(inline_resource target resource_file)

    set(inline_resources_dir ${CMAKE_CURRENT_BINARY_DIR}/${target}_InlineResources)
    file(MAKE_DIRECTORY ${inline_resources_dir})

    get_filename_component(resource_name ${resource_file} NAME)
    get_filename_component(resource_file_absolute ${resource_file} ABSOLUTE)

    set(config_extra_files ${generate_inline_resource} ${inline_resource_template})

    add_custom_command(
            OUTPUT ${inline_resources_dir}/${resource_name}.cpp
            DEPENDS ${resource_file} ${config_extra_files}
            COMMAND ${CMAKE_COMMAND} -P ${generate_inline_resource}
                ${target} ${resource_file_absolute} ${inline_resource_template}
    )

    target_sources(${target} PUBLIC ${inline_resources_dir}/${resource_name}.cpp ${resource_file} ${config_extra_files})

endfunction(inline_resource)

function(inline_resources target)

    foreach(resource_file ${ARGN})
        inline_resource(${target} ${resource_file})
    endforeach(resource_file)

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
