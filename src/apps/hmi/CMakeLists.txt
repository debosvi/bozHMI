
# include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_AUTOMOC ON)


set(BOZ_APP_HMI_BIN boz-app-hmi)

set(BOZ_APP_HMI_SRCS 
    main.cpp
    bozcentralclient.cpp
    )

set(BOZ_APP_HMI_HDRS 
    bozcentralclient.h
    )

add_executable(${BOZ_APP_HMI_BIN} 
    ${BOZ_APP_HMI_SRCS}
    )
    
qt5_use_modules(${BOZ_APP_HMI_BIN} Declarative)

target_link_libraries(${BOZ_APP_HMI_BIN} 
    websockets
    )

install(TARGETS ${BOZ_APP_HMI_BIN}
    DESTINATION ${BINARY_INSTALL_DIR}
    PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ 
    )
