
set(CMAKE_PREFIX_PATH ${BOZ_QT5_CMAKE_FIND_DIR})
find_package(Qt5WebKitWidgets REQUIRED)
include_directories(${Qt5WebKitWidgets_INCLUDE_DIRS})

set(CMAKE_PREFIX_PATH /usr/share/rtd/contribs/lib/cmake)
find_package(Skarnet REQUIRED)
message(STATUS "Skarnet found: " ${SKARNET_VERSION_STRING})
include_directories(${SKARNET_INCLUDE_DIRS})
link_directories(${SKARNET_LIBRARY_DIRS})

