#pragma once

#include "types.h"

#define GAME_ABORTED -1
#define NO_WINNER_DRAW 0
#define PLAYER_X 1
#define PLAYER_O 2

int launch_game(GameSettings* settings); 
