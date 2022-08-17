#pragma once

#include "types.h"

MenuSelection display_menu(int silent);
void display_settings(GameSettings* settings);
void display_board(GameState* state); 
void display_winner(int winner); 

int prompt_move(int* x, int* y, int player);
int modify_settings(GameSettings* settings);
