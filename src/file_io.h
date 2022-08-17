#pragma once

#include "types.h"
#include "linked_list.h"

int read_settings(GameSettings* settings, char* path);
int write_log(LinkedList* log, GameSettings* settings);
