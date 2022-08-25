# to create an interface library in cmake

function(create_interface_lib)

    # ----------------------------------------------------------
    # step 1: parse cmake arguments
    # ----------------------------------------------------------

    set(options VERBOSE)
    set(oneValueArgs NAME CONFIG)
    set(multiValueArgs LIBS)
    cmake_parse_arguments(LIB "${options}" "${oneValueArgs}"
                        "${multiValueArgs}" ${ARGN} )

    if(${LIB_VERBOSE})
    message("name: " ${LIB_NAME})
    message("libs: " ${LIB_LIBS})
    message("config: " ${LIB_CONFIG})
    endif()

    # ----------------------------------------------------------
    # step 2: create interface library
    # ----------------------------------------------------------

    if(CONFIG_${LIB_CONFIG})

    add_library(${LIB_NAME} INTERFACE)
    target_link_libraries(${LIB_NAME} INTERFACE ${LIB_LIBS})

    foreach(LIB ${LIB_LIBS})
        add_subdirectory(${LIB})
        if(VERBOSE)
        message("added interface sublib: " ${LIB})
        endif()
    endforeach()
    endif()

endfunction(create_interface_lib)



