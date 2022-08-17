#pragma once

/** Minimum and maximum values for n/m/k */
#define MIN_VALUE 3
#define MAX_VALUE 9

/**
 * @brief Enumeration for menu options.
 */
typedef enum {
    EXIT, 
    SHOW_SETTINGS, 
    NEW_GAME, 
    VIEW_LOG, 
    SAVE_LOG,
    EDIT_SETTINGS
} MenuSelection;

/**
 * @brief Specifies the dimensions of the board. 
 */
typedef struct {
    int m_width, n_height, k_row; 
} GameSettings; 

/**
 * @brief Maintains the game state. 
 */
typedef struct {
    int** board; 

    GameSettings* settings; 
} GameState; 
