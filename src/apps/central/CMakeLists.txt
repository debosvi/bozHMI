
# include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_definitions(-DINSTALL_DATADIR="/usr/share/boz/hmi")

set(BOZ_WS_APPS_BIN boz-ws-apps)

set(BOZ_WS_APPS_SRCS 
    sighandlers.c
    channel-protocols.c
    channel-http.c
    channel-apps.c
    main.c
    )

add_executable(${BOZ_WS_APPS_BIN} 
    ${BOZ_WS_APPS_SRCS}
    )
    
target_link_libraries(${BOZ_WS_APPS_BIN} 
    websockets
    )
