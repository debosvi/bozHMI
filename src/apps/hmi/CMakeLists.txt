
set(CMAKE_AUTOMOC ON)

set(HMI_BIN boz-hmi)

set(MAIN_HDRS 
    centralcentral.h
    )

set(MAIN_SRCS 
    centralclient.cpp
    main.cpp
    )

QT5_ADD_RESOURCES(RCC_SRCS qml.qrc)

add_executable(${HMI_BIN} 
    ${RCC_SRCS}
    ${MOC_SRCS}
    ${MAIN_SRCS}
    )

qt5_use_modules(${HMI_BIN} Gui Qml WebSockets)
    
target_link_libraries(${HMI_BIN} 
    
    )

install(TARGETS ${HMI_BIN}
    DESTINATION ${BINARY_INSTALL_DIR}
    PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ 
    )
