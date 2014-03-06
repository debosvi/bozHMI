
set(NX_JSON_DUMP_BIN nxjson_dump)

add_executable(${NX_JSON_DUMP_BIN}
    dump.c
    load_save.c
    main.c
    )

target_link_libraries(${NX_JSON_DUMP_BIN}
    nxjson
    )
