
set(CMAKE_AUTOMOC ON)

set(CENTRAL_BIN boz-central)

set(MAIN_HDRS 
    centralserver.h
    )

set(MAIN_SRCS 
    centralserver.cpp
    main.cpp
    )

add_executable(${CENTRAL_BIN} 
    ${MOC_SRCS}
    ${MAIN_SRCS}
    )

qt5_use_modules(${CENTRAL_BIN} WebSockets)
    
target_link_libraries(${CENTRAL_BIN} 
    
    )

install(TARGETS ${CENTRAL_BIN}
    DESTINATION ${BINARY_INSTALL_DIR}
    PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ 
    )
