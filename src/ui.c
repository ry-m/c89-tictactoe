#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ui.h"
#include "game.h"

/**
 * @brief Display the menu to the user and prompt for input.
 * 
 * @return MenuSelection choice
 */
MenuSelection display_menu(int silent) {
    char input[48];
    int selection;

    if (!silent) {
        printf(
            "======= Tic-Tac-Toe =======\n"
            "| (1) Exit game           |\n"
            "| (2) View settings       |\n"
            "| (3) New game            |\n"
            "| (4) View game log       |\n"
            "| (5) Save log to file    |\n"
            "| (6) Edit board size     |\n"
            "===========================\n"
        );
    }
    
    do {
        printf(">> Select an option:\n");
        scanf("%s", input); 
        selection = atoi(input) - 1;
    } while (selection < EXIT || selection > EDIT_SETTINGS + 1); 

    return selection;
}

/**
 * @brief Displays the current settings to the user.
 * 
 * @param settings Game settings
 */
void display_settings(GameSettings* settings) {
    printf(
        "===========================\n"
        "| M=%d\n"
        "| N=%d\n"
        "| K=%d\n"
        "===========================\n",
        settings->m_width, settings->n_height, settings->k_row
    );
}

/**
 * @brief Display the game board to the console.
 * 
 * @param state Game state
 */
void display_board(GameState* state) {
    int i, j, k;
    int width = state->settings->m_width; 
    int height = state->settings->n_height;
    int current; 

    /** Print header */ 
    for (k = 1; k <= width; k++) {
        printf("   %d", k); 
    }

    printf("\n");
    
    for (j = 1; j <= height; j++) {
        for (k = 1; k <= width; k++) {
            printf("----"); 
        }

        printf("--\n");

        printf("%d|", j);
        for (i = 1; i <= width; i++) {
            current = state->board[i-1][j-1];
            printf(
                " %c |", 
                current == 0 ? ' ' : (current == 1 ? 'X' : 'O')
            ); 
        }

        printf("\n"); 
    }

    /** Print footer */
    for (k = 1; k <= width; k++) {
        printf("----"); 
    }

    printf("--\n");
}

/**
 * @brief Display the result of the game
 * 
 * @param winner Winner
 */
void display_winner(int winner) {
    switch (winner) {
        case NO_WINNER_DRAW:
            printf("It's a draw!\n");
            break; 
        case GAME_ABORTED:
            printf("Game aborted!\n"); 
            break; 
        case PLAYER_X:
            printf("Player X wins!\n"); 
            break; 
        case PLAYER_O:
            printf("Player O wins!\n");
            break; 
        default: break;
    }
}

/**
 * @brief Retrieve user input for a move, or 'exit' to quit.
 * 
 * @param x X
 * @param y Y
 * @param player Current player
 * @return int 1 if exit
 */
int prompt_move(int* x, int* y, int player) {
    char input[48]; 

    /** Loops forever until returning */
    while (1) {
        printf("Player %c: x,y: \n", player == 1 ? 'X' : 'O');
        scanf("%s", input); 

        if (strcmp(input, "exit") == 0) {
            return 0; /** Not running */
        } else {
            if (sscanf(input, "%d,%d", x, y) == 2) {
                /** We recieved the two integers */
                return 1; 
            } else {
                /** Invalid input */
                fprintf(stderr, "Enter coordinates in format x,y or type 'exit' to quit.\n");
            }
        }
    }
}

/**
 * @brief Prompt the user to modify the game settings.
 * 
 * @param settings Game settings. 
 * @return int 1 if the settings were modified.
 */
int modify_settings(GameSettings* settings) {
    char input[48]; 
    int m, n, k;

    printf(
        "Enter values for m/n/k in the format <m>,<n>,<k>\n"
        "Type 'exit' to cancel.\n"
    );

    while (1) {
        scanf("%s", input);

        if (strcmp(input, "exit") == 0) {
            /** Don't modify the settings */
            return 0; 
        } else {
            if (sscanf(input, "%d,%d,%d", &m, &n, &k) == 3) {
                /** Validate the three integers */
                if (m >= MIN_VALUE && m <= MAX_VALUE
                    && n >= MIN_VALUE && n <= MAX_VALUE
                    && k >= MIN_VALUE && k <= MAX_VALUE
                    && k <= n && k <= m
                ) {
                    /** All good, modify the settings */
                    settings->m_width = m; 
                    settings->n_height = n; 
                    settings->k_row = k;

                    return 1; 
                }
            } else {
                /** Invalid input */
                fprintf(stderr, "error: unexpected input format. Try again.\n");
            }
        }
    }
}
