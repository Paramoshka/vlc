//
// Created by ivan on 24.03.24.
//

#ifndef VLC_JS_VLC_H
#define VLC_JS_VLC_H
#include "vlc/vlc.h"
#include "memory"
#include "HLS.h"
#include <cstdio>
#include <cstdint>

class VLC {
public:
    VLC();
    ~VLC();
    void playMedia(const char *path_media);



private:
    libvlc_instance_t *vlc_instance{};
    libvlc_media_player_t *media_player{};
    libvlc_media_t *media{};
    const char *options = "--rtsp-tcp";
    char smem_options[256];

// Video prerender and postrender callbacks not implemented.

};


#endif //VLC_JS_VLC_H
