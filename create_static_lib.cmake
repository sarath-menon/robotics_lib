# function(create_static_lib LIB_NAME include_dirs PUBLIC_LIB_DEP PRIVATE_LIB_DEP)

#     add_library(${MODULE_NAME} STATIC ${CPP_FILES})

#     target_include_directories(${MODULE_NAME} PUBLIC ${include_dirs})
#     target_link_libraries(${MODULE_NAME} PUBLIC ${PUBLIC_LIB_DEP})
#     target_link_libraries(${MODULE_NAME} PRIVATE ${PRIVATE_LIB_DEP})

#     message("added static lib: " ${LIB_NAME})
# endfunction()


function(create_static_lib)

    # ----------------------------------------------------------
    # step 1: parse cmake arguments
    # ----------------------------------------------------------

    # set(options )
    set(oneValueArgs NAME CONFIG)
    set(multiValueArgs CPP_FILES INCLUDE_DIRS PUBLIC_LIB_DEP PRIVATE_LIB_DEP)
    cmake_parse_arguments(LIB "${options}" "${oneValueArgs}"
                        "${multiValueArgs}" ${ARGN} )

    message("static lib name: " ${LIB_NAME})
    message("cpp files: " ${LIB_CPP_FILES})
    message("include dirs: " ${LIB_INCLUDE_DIRS})
    message("public lib deps: " ${LIB_PUBLIC_LIB_DEP})
    message("private lib deps:: " ${LIB_PRIVATE_LIB_DEP})
    message("config: " ${LIB_CONFIG})
    # message("optional: " ${LIB_OPTIONAL})

    # ----------------------------------------------------------
    # step 2: create static library
    # ----------------------------------------------------------

    if(CONFIG_${LIB_CONFIG})

    add_library(${LIB_NAME} STATIC ${LIB_CPP_FILES})

    target_include_directories(${LIB_NAME} PUBLIC ${LIB_INCLUDE_DIRS})
    target_link_libraries(${LIB_NAME} PUBLIC ${LIB_PUBLIC_LIB_DEP})
    target_link_libraries(${LIB_NAME} PRIVATE ${LIB_PRIVATE_LIB_DEP})

    endif()

endfunction(create_interface_lib_new)




