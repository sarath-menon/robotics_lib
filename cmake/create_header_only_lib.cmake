# to create a static library in cmake

function(create_header_only_lib)

    # ----------------------------------------------------------
    # step 1: parse cmake arguments
    # ----------------------------------------------------------

    set(options VERBOSE)
    set(oneValueArgs NAME)
    set(multiValueArgs INCLUDE_DIRS DEP)
    cmake_parse_arguments(LIB "${options}" "${oneValueArgs}"
                        "${multiValueArgs}" ${ARGN} )

    if(${LIB_VERBOSE})
    message("header only lib name: " ${LIB_NAME})
    message("include dirs: " ${LIB_INCLUDE_DIRS})
    message("lib deps: " ${LIB_DEP})
    endif()

    # ----------------------------------------------------------
    # step 2: create header only library
    # ----------------------------------------------------------

    add_library(${LIB_NAME} INTERFACE)
    target_include_directories(${LIB_NAME} INTERFACE ${LIB_INCLUDE_DIRS})
    target_link_libraries(${LIB_NAME} INTERFACE ${LIB_DEP})

    if(VERBOSE)
        message("added header only lib: " ${LIB_NAME})
    endif()


endfunction(create_header_only_lib)




