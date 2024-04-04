//
// Created by ivan on 24.03.24.
//

#include "vlc.h"


VLC::VLC() {
    const char * const vlc_args[] = {
            //"--verbose=2", // Be much more verbose then normal for debugging purpose
            "--sout=transcode{acodec=mp3}:duplicate{dst=display{delay=6000}",
            "dst=gather:std{mux=mpeg1,dst=:8080/stream.mp3,access=http},select=\"novideo\"} "
    };

    vlc_instance = libvlc_new(sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args);

}

VLC::~VLC() {
   // free(vlc_instance);
  //  free(media_player);
}

void VLC::playMedia(const char *path_media) {
    media = libvlc_media_new_location(vlc_instance,path_media);
    media_player = libvlc_media_player_new_from_media(media);
    libvlc_media_player_play(media_player);
    sleep(30);
    libvlc_media_release(media);
}





