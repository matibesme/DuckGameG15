#include "pathmaker.h"

static const char* DATA_RELATIVE_PATH = "data";
static const char* PLATFORMS_RELATIVE_PATH = "/platforms/";
static const char* BACKGROUNDS_RELATIVE_PATH = "/backgrounds/";
static const char* EXTENSION = ".png";

#include <iostream>
PathMaker::PathMaker(){

}
std::string PathMaker::get_platform_path(std::string platform_type){
    std::string path = std::string(DATA_RELATIVE_PATH) + std::string(PLATFORMS_RELATIVE_PATH) + platform_type + std::string(EXTENSION);
    return path;
}

std::string PathMaker::get_background_path(std::string background_type){
    std::string path = std::string(DATA_RELATIVE_PATH) + std::string(BACKGROUNDS_RELATIVE_PATH) + background_type + std::string(EXTENSION);

    return path;
}