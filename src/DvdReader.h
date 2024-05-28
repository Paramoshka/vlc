//
// Created by ivan on 16.03.24.
//

#ifndef VLC_JS_DVDREADER_H
#define VLC_JS_DVDREADER_H
#include "dvdnav/dvdnav.h"
#include "HLS.h"
#include <fcntl.h>
#include <cstdio>
#include <unistd.h>
#include "BufferReader.h"

/* shall we use libdvdnav's read ahead cache? */
#define DVD_READ_CACHE 1
#define TS_LENGTH 10
/* which is the default language for menus/audio/subpictures? */

#define DVD_LANGUAGE "en"

#ifdef _WIN32
#define S_IRWXG 0
#endif

/**
 * This class serve dvd disk, accept command and return buffer
 * */
class DvdReader {

public:
    DvdReader(const char* path_dvd);
    ~DvdReader();
    uint8_t *buf;
    uint8_t *ts_buf;
    /* the main reading function */
    int writeBuffer();

protected:
    dvdnav_t *dvdnav{};
    uint8_t mem[DVD_VIDEO_LB_LEN];
    uint8_t ts_mem[DVD_VIDEO_LB_LEN * TS_LENGTH];
    int output_fd;
    int result, event, len;
    int finished;
    uint8_t ts_chunk;
};


#endif //VLC_JS_DVDREADER_H
