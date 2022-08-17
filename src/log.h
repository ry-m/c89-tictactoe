#pragma once

#include "linked_list.h"

/**
 * @brief Different types of things to log. 
 */
typedef enum {
    TURN,
    GAME_SETTINGS,
    GAME_NUM
} LogType; 

/**
 * @brief Log item
 */
typedef struct {
    LogType type; 
    int v1, v2, v3, v4;
} LogItem; 

void add_to_log(LinkedList* list, LogType type, int v1, int v2, int v3, int v4);
void print_log(void* data);
