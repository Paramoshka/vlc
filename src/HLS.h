//
// Created by ivan on 17.03.24.
//

#ifndef VLC_JS_HLS_H
#define VLC_JS_HLS_H


#include <cstdint>
#include "unistd.h"
#include "fcntl.h"
#include <ctime>
#include <iostream>

class HLS {

public:
    HLS();
    ~HLS();
    void generate_ts(uint8_t *buf, const char *path_hls, int len);
protected:
    int file_ts_fd;
    std::basic_string<char> file_name;
};


#endif //VLC_JS_HLS_H
