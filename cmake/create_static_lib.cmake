function(create_static_lib)

    # ----------------------------------------------------------
    # step 1: parse cmake arguments
    # ----------------------------------------------------------

    set(options VERBOSE)
    set(oneValueArgs NAME CONFIG)
    set(multiValueArgs CPP_FILES INCLUDE_DIRS PUBLIC_LIB_DEP PRIVATE_LIB_DEP)
    cmake_parse_arguments(LIB "${options}" "${oneValueArgs}"
                        "${multiValueArgs}" ${ARGN} )

    if(${LIB_VERBOSE})
    message("static lib name: " ${LIB_NAME})
    message("cpp files: " ${LIB_CPP_FILES})
    message("include dirs: " ${LIB_INCLUDE_DIRS})
    message("public lib deps: " ${LIB_PUBLIC_LIB_DEP})
    message("private lib deps:: " ${LIB_PRIVATE_LIB_DEP})
    message("config: " ${LIB_CONFIG})
    endif()

    # ----------------------------------------------------------
    # step 2: create static library
    # ----------------------------------------------------------

    if(CONFIG_${LIB_CONFIG})

    add_library(${LIB_NAME} STATIC ${LIB_CPP_FILES})

    target_include_directories(${LIB_NAME} PUBLIC ${LIB_INCLUDE_DIRS})
    target_link_libraries(${LIB_NAME} PUBLIC ${LIB_PUBLIC_LIB_DEP})
    target_link_libraries(${LIB_NAME} PRIVATE ${LIB_PRIVATE_LIB_DEP})

    if(VERBOSE)
        message("added static lib: " ${LIB_NAME})
    endif()

    endif()

endfunction(create_static_lib)




