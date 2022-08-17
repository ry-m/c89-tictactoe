#include <stdlib.h>
#include <stdio.h>

#include "game.h"
#include "ui.h"
#include "linked_list.h"
#include "log.h"
#include "file_io.h"

/**
 * @brief Initialise the memory for the board array. 
 * 
 * @param board Board array
 * @param settings Game settings
 */
void init_board(GameState* state) {
    int i; 
    int columns = state->settings->m_width;
    int rows = state->settings->n_height;
    
    state->board = (int**)calloc(rows, sizeof(int*)); 
    for (i = 0; i < rows; i++) {
        state->board[i] = (int*)calloc(columns, sizeof(int)); 
    }
}

/**
 * @brief Free memory for game board.
 * 
 * @param board Game board.
 */
void free_board(int** board) {
    int i; 

    for (i = 0; i < sizeof(board) / sizeof(int); i++) {
        free(board[i]); 
    }

    free(board);
}

/**
 * @brief Reset board ready for new game. Does not reset settings.
 * 
 * @param state Game state.
 */
void reset_game(GameState* state) {
    free_board(state->board);
    init_board(state);
}

/**
 * @brief Check if a move is valid
 * 
 * @param x X
 * @param y Y
 * @param settings Settings for M/N validation
 * @return int true if valid
 */
int is_valid_move(int x, int y, GameState* state) {
    return x > 0 && x <= state->settings->m_width
        && y > 0 && y <= state->settings->n_height
        && state->board[x-1][y-1] == 0;
}

/**
 * @brief Check if the move is a winning move.
 * 
 * @param state Game state
 * @param player Player of the move
 * @param x X
 * @param y Y
 * @return int 0 if not winner yet, or player ID if they won.
 */
int check_winner(GameState* state, int player, int x, int y) {
    int m = state->settings->m_width; 
    int n = state->settings->n_height; 
    int k = state->settings->k_row; 

    int i, j; 
    int k_current = 0; 

    /** Check row */ 
    for (i = 1; i < m; i++) {
        if (state->board[i-1][y-1] == player) {
            k_current++; 
        } else {
            k_current = 0; 
        }

        if (k_current >= k) break; 
    }

    if (k_current >= k) {
        return player; 
    }

    k_current = 0;

    /** Check column */ 
    for (j = 1; j < n; j++) {
        if (state->board[x-1][j-1] == player) {
            k_current++; 
        } else {
            k_current = 0; 
        }

        if (k_current >= k) break; 
    }

    if (k_current >= k) {
        return player; 
    }

    k_current = 0; 

    /** Check diagonal */
    i = x; 
    j = y; 
    /** Go to edge */
    while (i != 1 && j != 1) {
        i--; 
        j--;
    }

    while (i < m && j < n) {
        if (state->board[i-1][j-1] == player) {
            k_current++; 
        } else {
            k_current = 0; 
        }

        if (k_current >= k) break; 

        i++;
        j++;
    }

    return NO_WINNER_DRAW; 
}

/**
 * @brief Play a new game. 
 * 
 * @param state Game state
 * @return int winner ID
 */
int new_game(GameState* state, LinkedList* log) {
    int running = 1; 
    int player = PLAYER_X; /** Current player */
    int turns = 1; 
    int x = 0, y = 0; 
    int winner = NO_WINNER_DRAW;
    int occupied_spaces = state->settings->m_width * state->settings->n_height; 

    display_board(state);

    while (running) {
        /** Set to false if the user types in 'exit' */
        running = prompt_move(&x, &y, player); 

        if (is_valid_move(x, y, state)) {
            /** Execute the move */
            state->board[x-1][y-1] = player; 
            occupied_spaces--;
            turns++;
            add_to_log(log, TURN, turns, player, x, y);

            winner = check_winner(state, player, x, y);
            if (!winner) {
                if (occupied_spaces == 0) {
                    /** No winner, it's a draw */
                    return NO_WINNER_DRAW; 
                }
                /** If no winner, swap players */
                player = player == PLAYER_X ? PLAYER_O : PLAYER_X; 
            } else {
                return winner; 
            }

            display_board(state);
        } else {
            fprintf(stderr, "Invalid move. Try again or type 'exit'.\n"); 
        }
    }

    return GAME_ABORTED; 
}

/**
 * @brief Launches the game by running the main menu loop.
 * 
 * @param settings Game settings
 * @return int status
 */
int launch_game(GameSettings* settings) {
    GameState* state = (GameState*)malloc(sizeof(GameState));
    LinkedList* log = (LinkedList*)malloc(sizeof(LinkedList));
    MenuSelection selection = -1; 
    /** Show the menu again? */
    int silent = 0; 
    int num_games = 0;

    state->settings = settings;
    new_list(log);
    init_board(state);

    add_to_log(
        log, 
        GAME_SETTINGS, 
        settings->m_width, 
        settings->n_height, 
        settings->k_row,
        0
    );

    /** Main game loop (menu) */
    while (selection != EXIT) {
        selection = display_menu(silent);
        silent = 0;

        switch(selection) {
            case EXIT: 
                break; 
            case SHOW_SETTINGS:
                display_settings(state->settings); 
                silent = 1;
                break; 
            case NEW_GAME:
                num_games++;
                add_to_log(log, GAME_NUM, num_games, 0, 0, 0);
                display_winner(new_game(state, log));
                reset_game(state);
                break;
            case VIEW_LOG:
                disp(log, &print_log);
                break; 
            case SAVE_LOG:
                write_log(log, state->settings);
                break;
            case EDIT_SETTINGS:
                if (modify_settings(state->settings)) 
                    reset_game(state);
                break;
            default: 
                break; 
        }
    }

    /** Free memory. Settings struct free'd in main.c */
    free_board(state->board);
    free(state);
    free_list(log);

    return 0;
}
