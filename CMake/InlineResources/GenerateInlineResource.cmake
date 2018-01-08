cmake_minimum_required(VERSION 3.9)

set(inline_resource_template ${CMAKE_ARGV5})

function(generate_inline_resource target resource_file)

    set(inline_resources_dir ${CMAKE_CURRENT_BINARY_DIR}/${target}_InlineResources)
    file(MAKE_DIRECTORY ${inline_resources_dir})

    get_filename_component(resource_name ${resource_file} NAME)

    file(READ ${resource_file} resource_file_content HEX)

    string(REGEX MATCHALL "(..)" chars ${resource_file_content})

    foreach(char ${chars})
        if(resource_content)
            math(EXPR not_end_of_line "${index} % 18")

            if(not_end_of_line)
                set(resource_content "${resource_content}, 0x${char}")
            else(not_end_of_line)
                set(resource_content "${resource_content},\n        0x${char}")
            endif(not_end_of_line)
        else(resource_content)
            set(resource_content "0x${char}")
        endif(resource_content)

        math(EXPR index "${index} + 1")
    endforeach(char)

    configure_file(${inline_resource_template} ${inline_resources_dir}/${resource_name}.cpp)

endfunction(generate_inline_resource)

generate_inline_resource(${CMAKE_ARGV3} ${CMAKE_ARGV4})
