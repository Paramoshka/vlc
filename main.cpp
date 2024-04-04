#include <iostream>
#include "src/vlc.h"


int main() {
    auto pathHTTP = "https://web.landoffreedom.ru/movie/2.ISO";
    auto vlc = new VLC();
    vlc->playMedia(pathHTTP);
    std::cout << "Server is running" << std::endl;
    return 0;
}
