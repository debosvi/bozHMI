
set(NX_JSON_LIB nxjson)
add_definitions(-D_XOPEN_SOURCE=500)

file(COPY nxjson.h
    DESTINATION ${PROJECT_BINARY_DIR}/include
    USE_SOURCE_PERMISSIONS
    )

add_library(${NX_JSON_LIB} SHARED
    nxjson.c
    )

target_link_libraries(${NX_JSON_LIB}
    datastruct stddjb
    )

install(TARGETS ${NX_JSON_LIB}
    DESTINATION ${LIBRARY_INSTALL_DIR}
    PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ GROUP_WRITE WORLD_READ
    )
