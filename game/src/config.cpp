#include "config.h"

std::string assets_path_joiner(std::string file) {
    std::string file_s(file);
    if (file_s.size() == 0 || file_s[0] != '/') file_s = "/" + file_s;

    return std::string(GAME_ASSETS_FOLDER) + file_s;
}
