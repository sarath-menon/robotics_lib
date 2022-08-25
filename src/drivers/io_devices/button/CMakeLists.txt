# set(MODULE_NAME button)


# # list of c++ source files
# set(CPP_FILES
# src/${MODULE_NAME}.cpp
# )

# # list of directories to include
# set(INCLUDE_DIRS
# include
# )

# # list of library dependendcies
# set(PUBLIC_LIB_DEP
# rl_common
# )

# set(PRIVATE_LIB_DEP
# zephyr
# zephyr_interface
# )

# ####### Do not modify !
# create_static_lib(${MODULE_NAME} ${INCLUDE_DIRS} ${PUBLIC_LIB_DEP} ${PRIVATE_LIB_DEP})



create_static_lib(NAME button
                    CONFIG 
                            ENABLE_ROBOTICS_LIB
                    CPP_FILES
                            src/button.cpp
                    INCLUDE_DIRS
                            include
                    PUBLIC_LIB_DEP
                            rl_common
                    PRIVATE_LIB_DEP
                            zephyr
                            zephyr_interface
                    )