# Template for pure interface library

set(LIB_NAME communication)

# list of libs to combine as one interface lib
set(SUB_LIBS 
usb_console
# syslink
uart_dma
)

####### Do not modify !

add_library(${LIB_NAME} INTERFACE)

target_link_libraries(${LIB_NAME} INTERFACE ${SUB_LIBS})

foreach(LIB ${SUB_LIBS})
    add_subdirectory(${LIB})
endforeach()


