//
// Created by ivan on 28.05.24.
//

#ifndef VLC_JS_BUFFERREADER_H
#define VLC_JS_BUFFERREADER_H


#include <cstdint>
#include <cstdio>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavformat/avio.h>
#include <libavutil/file.h>
#include <libavutil/mem.h>

class BufferReader {

    struct buffer_data {
        uint8_t *ptr{};
        size_t size{}; ///< size left in the buffer
    };

    static int read_packet(void *opaque, uint8_t *buf, int buf_size);

    static AVFormatContext *fmt_ctx;
    static AVIOContext *avio_ctx;
    static uint8_t *buffer;
    static uint8_t *avio_ctx_buffer;
    static size_t buffer_size;
    static size_t avio_ctx_buffer_size;
    static int ret;
    static struct buffer_data bd;

public:
    static int read_buffer(uint8_t* ptr_buf, size_t size);

};


#endif //VLC_JS_BUFFERREADER_H
