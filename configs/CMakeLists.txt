
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/nginx.conf.in 
    ${CMAKE_CURRENT_BINARY_DIR}/nginx.conf
    @ONLY
    )

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/nginx.conf
    DESTINATION /etc/nginx/sites-available/
    PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ 
    RENAME bozhmi.conf
    )

