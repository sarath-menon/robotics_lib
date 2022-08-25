function(create_interface_lib)

    # ----------------------------------------------------------
    # step 1: parse cmake arguments
    # ----------------------------------------------------------

    # set(options )
    set(oneValueArgs NAME CONFIG)
    set(multiValueArgs LIBS)
    cmake_parse_arguments(LIB "${options}" "${oneValueArgs}"
                        "${multiValueArgs}" ${ARGN} )

    message("name: " ${LIB_NAME})
    message("libs: " ${LIB_LIBS})
    message("config: " ${LIB_CONFIG})
    # message("optional: " ${LIB_OPTIONAL})

    # ----------------------------------------------------------
    # step 2: create static library
    # ----------------------------------------------------------

    if(CONFIG_${LIB_CONFIG})

    add_library(${LIB_NAME} INTERFACE)
    target_link_libraries(${LIB_NAME} INTERFACE ${LIB_LIBS})

    foreach(LIB ${LIB_LIBS})
        add_subdirectory(${LIB})
        message("added interface sublib: " ${LIB})
    endforeach()
    endif()

endfunction(create_interface_lib)



