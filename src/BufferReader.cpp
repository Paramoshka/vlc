//
// Created by ivan on 28.05.24.
//

#include "BufferReader.h"

int BufferReader::read_packet(void *opaque, uint8_t *buf, int buf_size) {
    auto *bd = (struct buffer_data *)opaque;
    buf_size = FFMIN(buf_size, bd->size);

    if (!buf_size)
        return AVERROR_EOF;
    printf("ptr:%p size:%zu\n", bd->ptr, bd->size);

    /* copy internal buffer data to buf */
    memcpy(buf, bd->ptr, buf_size);
    bd->ptr  += buf_size;
    bd->size -= buf_size;

    return buf_size;
}

int BufferReader::read_buffer(uint8_t *ptr_buf, size_t size) {
    bd.ptr = ptr_buf;
    bd.size = size;

    avio_ctx_buffer = static_cast<uint8_t *>(av_malloc(avio_ctx_buffer_size));
    avio_ctx = avio_alloc_context(avio_ctx_buffer, avio_ctx_buffer_size,0, &bd, &read_packet, nullptr, nullptr);
    return 0;
}


