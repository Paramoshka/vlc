cmake_minimum_required(VERSION 3.27)
project(vlc_js)

set(CMAKE_CXX_STANDARD 23)

add_executable(vlc_js main.cpp
        src/DvdReader.cpp
        src/DvdReader.h
        src/Utils.cpp
        src/Utils.h
        src/HLS.cpp
        src/HLS.h
        src/BufferReader.cpp
        src/BufferReader.h
)

#oat
message(STATUS "trying find oat lib oat/lib/oatpp-1.3.0")
find_library(OATLIB  NAMES oatpp PATHS oat/lib/oatpp-1.3.0)
message(STATUS ${OATLIB})
target_link_libraries(${PROJECT_NAME} ${OATLIB})
include_directories(oat/include/oatpp-1.3.0/oatpp)

#dvdnav
message(STATUS "trying find dvdnav lib /usr/lib")
find_library(DVD_NAV NAMES dvdnav PATHS /usr/lib)
message(STATUS ${DVD_NAV} "if not found try install libdvdnav-dev")


find_library(AVCODEC_LIBRARY avcodec)
message(STATUS ${AVCODEC_LIBRARY})
find_library(AVFORMAT_LIBRARY avformat)
message(STATUS ${AVFORMAT_LIBRARY})

target_link_libraries(${PROJECT_NAME} ${DVD_NAV} ${AVCODEC_LIBRARY} ${AVFORMAT_LIBRARY})

#vlc
#target_link_libraries(${PROJECT_NAME} -lvlc)
