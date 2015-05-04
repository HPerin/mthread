cmake_minimum_required(VERSION 3.0)
project(mthread)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)

set(SOURCE_FILES src/main.c
                 src/mthread.c
                 src/mmutex.c
                 src/mlist.c
                 src/metcb.c
                 src/mcontrol.c)

set(HEADER_FILES include/mthread.h
                 include/mmutex.h
                 include/mlist.h
                 include/mdata.h
                 include/metcb.h
                 include/mcontrol.h)

add_executable(mthread ${SOURCE_FILES} ${HEADER_FILES} include/mvector.h src/mvector.c)