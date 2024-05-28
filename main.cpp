#include <iostream>
#include "src/DvdReader.h"


int main() {
    auto pathHTTP = "https://web.landoffreedom.ru/movie/2.ISO";
    auto dvd = new DvdReader(pathHTTP);
    dvd->writeBuffer();
    std::cout << "Server is running" << std::endl;
    return 0;
}
