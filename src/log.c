#include <stdlib.h>
#include <stdio.h>

#include "log.h" 

/**
 * @brief Log an item to the logger
 * 
 * @param list Log list
 * @param type LogType
 * @param values values
 */
void add_to_log(LinkedList* list, LogType type, int v1, int v2, int v3, int v4) {
    LogItem* item = (LogItem*)malloc(sizeof(LogItem));
    item->type = type; 
    item->v1 = v1;
    item->v2 = v2;
    item->v3 = v3;
    item->v4 = v4;

    insert_last(list, item);
}

/**
 * @brief Print function for printing log.
 * 
 * @param data Log item (node)
 */
void print_log(void* data) {
    LogItem* value = (LogItem*)data;

    switch (value->type) {
        case TURN:
            printf(
                "Turn: %d\nPlayer %c\n",
                value->v1,
                value->v2 == 1 ? 'X' : 'O'
            ); 

            printf("Location: %d,%d\n", value->v3, value->v4);
            break;
        case GAME_NUM:
            printf("Game #%d\n", value->v1);
            break; 
        case GAME_SETTINGS:
            printf("M=%d, N=%d, K=%d\n", value->v1, value->v2, value->v3);
            break; 
    }
}
