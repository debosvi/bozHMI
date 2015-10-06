
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/index.html.in 
    ${CMAKE_CURRENT_BINARY_DIR}/index.html
    @ONLY
    )

install(FILES jquery.js bozapps.js boz_wsconn.js central.js
    DESTINATION ${BOZ_WEB_ROOT_DIR}/js
    PERMISSIONS OWNER_READ GROUP_READ WORLD_READ
    )

install(FILES index.css
    DESTINATION ${BOZ_WEB_ROOT_DIR}/css
    PERMISSIONS OWNER_READ GROUP_READ WORLD_READ
    )

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/index.html
    DESTINATION ${BOZ_WEB_ROOT_DIR}
    PERMISSIONS OWNER_READ GROUP_READ WORLD_READ
    )

