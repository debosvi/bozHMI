

add_definitions(-DINSTALL_DATADIR="/usr/share/boz/hmi")
add_definitions(-DCENTRAL_WS_PORT=${BOZ_CENTRAL_WS_PORT})

add_subdirectory(central)
add_subdirectory(hmi)
