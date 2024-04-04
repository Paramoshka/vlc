//
// Created by ivan on 17.03.24.
//


#include <fstream>
#include "HLS.h"

void HLS::generate_ts(uint8_t *buf, const char *path_hls, int len) {
    std::time_t now = std::time(nullptr);
    std::tm *  time = std::localtime(&now);
    std::string timestamp = std::to_string(now) + "_" + std::to_string(time->tm_hour) + "_" + std::to_string(time->tm_min) + "_" + std::to_string(time->tm_sec) + ".ts";

    //std::ofstream file(timestamp, std::ios_base::app);
   // printf("timestamp: %s \n", timestamp.c_str());
    if (file_name != timestamp) {
        file_name = timestamp;
        file_ts_fd = open(timestamp.c_str(), O_CREAT | O_WRONLY, S_IRWXU | S_IRWXG);

    } else {
        write(file_ts_fd, buf, len);
    }
}

HLS::HLS() {
    file_ts_fd = 0;
}

HLS::~HLS() {

}
