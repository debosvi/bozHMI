
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_definitions(-DWEBPLUGIN_DIR="${PLUGINS_INSTALL_DIR}")
#add_definitions(-DCENTRAL_WS_PORT=${BOZ_CENTRAL_WS_PORT})

#set(BOZ_WS_APPS_BIN boz-ws-apps)

#set(BOZ_WS_APPS_SRCS 
#    sighandlers.c
#    channel-protocols.c
#    channel-http.c
#    channel-apps.c
#    main.c
#    )

#add_executable(${BOZ_WS_APPS_BIN} 
#    ${BOZ_WS_APPS_SRCS}
#    )
    
#target_link_libraries(${BOZ_WS_APPS_BIN} 
#    datastruct stddjb
#    websockets
#    nxjson
#    )

#install(TARGETS ${BOZ_WS_APPS_BIN}
#    DESTINATION ${BINARY_INSTALL_DIR}
#    PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ 
#    )

get_filename_component(DIRNAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
set(LOCALBIN_NAME boz-${DIRNAME})

set(${DIRNAME}_HDRS
    BOZ_Webpage.h
    )

set(${DIRNAME}_SRCS
    main.cpp
    BOZ_Webpage.cpp
    )

QT5_WRAP_CPP(${LOCALBIN_NAME}_HEADERS_MOC ${${DIRNAME}_HDRS})

add_executable(${LOCALBIN_NAME}
    ${${DIRNAME}_SRCS}
    ${${LOCALBIN_NAME}_HEADERS_MOC}
    )
target_link_libraries(${LOCALBIN_NAME}
    ${Qt5WebKitWidgets_LIBRARIES}
    )

install(TARGETS ${${DIRNAME}ORYNAME} RUNTIME DESTINATION ${BINARY_INSTALL_DIR})

