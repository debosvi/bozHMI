cmake_minimum_required (VERSION 2.8)
project (bozHMI)

include(project_ver.cmake)
include(ext_build/boz-build.cmake)
include(CTest)

include(tools.cmake)

#set (CMAKE_VERBOSE_MAKEFILE ON)

add_definitions(-fPIC)

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/include)

#add_subdirectory(include)

# to be removed later
set(BOZ_GLOBAL_TEST y)

add_subdirectory(configs)
add_subdirectory(src)

add_test_if_enable(test BOZ_GLOBAL_TEST)

include(package/package.cmake)
