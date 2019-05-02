#ifndef __GAME_CONFIG_H_IN__
#define __GAME_CONFIG_H_IN__

#include <string>

#define GAME_NAME "nome do jogo"
#define GAME_ASSETS_FOLDER "game/assets"

std::string assets_path_joiner(std::string file);

#define ASSETS_PATH(path) (assets_path_joiner(path).c_str())

#endif

