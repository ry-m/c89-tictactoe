#include <stdio.h>
#include <time.h>
#include <string.h>

#include "file_io.h"
#include "game.h"
#include "log.h"

/**
 * @brief Parse a settings file with the expected format of [n/m/k]=[integer]. Each value 
 * must be initialised. Case insensitive. 
 * 
 * @param settings Game settings struct
 * @param path Path to the settings file
 * @return int status (-1 == fail)
 */
int read_settings(GameSettings* settings, char* path) {
    /** ID is one of m/n/k */
    char id; 
    /** Value is any number between MIN_VALUE and MAX_VALUE */
    int value;
    /** True for each m/n/k value if found in file */
    int found_m, found_n, found_k;

    int i; 
    
    /** Open the file */
    FILE* file = fopen(path, "r"); 
    if (file == NULL) {
        perror("error");
        fclose(file);
        return -1; 
    }

    /** Expecting 3 sets of [n/m/k]=[integer] */
    for (i = 1; i <=3; i++) {
        if (fscanf(file, "%c=%d\n", &id, &value) != 2) {
            fprintf(
                stderr,
                "error: expecting file format [nmk]=[integer] for each line of  file.\n"
            ); 

            fclose(file);
            return -1; 
        }

        /** Validate the value */ 
        if (value < MIN_VALUE || value > MAX_VALUE) {
            fprintf(
                stderr, 
                "error: value of '%d' not in range %d-%d.\n", 
                value, MIN_VALUE, MAX_VALUE
            ); 

            fclose(file);
            return -1; 
        }

        /** Validate the id */
        switch (id) {
            case 'm': case 'M':
                settings->m_width = value; 
                found_m = 1; 
                break; 
            case 'n': case'N':
                settings->n_height = value; 
                found_n = 1; 
                break; 
            case 'k': case 'K':
                settings->k_row = value;
                found_k = 1; 
                break; 
            default: 
                fprintf(
                    stderr, 
                    "error: unknown identifier '%c'. Must be one of: n/m/k.\n",
                    id
                );

                fclose(file);
                return -1; 
        }
    }

    /** Check for any file errors after reading */
    if (ferror(file)) {
        perror("error"); 
        fclose(file);
        return -1; 
    }

    /** Check if all values initialised */ 
    if (!found_m || !found_n || !found_k) {
        fprintf(stderr, "error: must initialise all values for n, m, k.\n"); 
        fclose(file); 
        return -1; 
    }

    /** Validate size of the board */
    if (settings->k_row > settings->m_width || settings->k_row > settings->n_height) {
        fprintf(stderr, "error: k cannot be larger than m or n.\n");
        fclose(file);
        return -1; 
    }

    fclose(file);
    return 0;
}

/**
 * @brief Save the log to file. 
 * 
 * @param log Log 
 * @param settings Settings
 */
int write_log(LinkedList* log, GameSettings* settings) {
    FILE* output; 
    char file_name[48];
    int h, m, day, month;
    int i;
    Node* current; 
    LogItem* item;

    time_t now; 
    struct tm* local; 

    time(&now);
    local = localtime(&now);

    h = local->tm_hour; 
    m = local->tm_min;
    day = local->tm_mday; 
    month = local->tm_mon + 1;

	strcpy(file_name, "MNK_00-00-00_00-00_00-00.log");
	sprintf(
        file_name, 
        "MNK_%d-%d-%d_%02d-%02d_%02d-%02d.log", 
        settings->m_width, 
        settings->n_height, 
        settings->k_row, 
        h, m, day, month
    );

    output = fopen(file_name, "w");

    if (output == NULL) {
        perror("Failed to write log"); 
        return -1; 
    }

    current = log->head; 

    for (i = 1; i < log->count; i++) {
        item = (LogItem*)current->data; 

        switch (item->type) {
            case TURN:
                fprintf(output,
                    "Turn: %d\nPlayer %c\n",
                    item->v1,
                    item->v2 == 1 ? 'X' : 'O'
                ); 

                fprintf(output, "Location: %d,%d\n", item->v3, item->v4);
                break;
            case GAME_NUM:
                fprintf(output, "Game #%d\n", item->v1);
                break; 
            case GAME_SETTINGS:
                fprintf(output, "M=%d, N=%d, K=%d\n", item->v1, item->v2, item->v3);
                break; 
        }

        current = current->next; 
    }

    if (ferror(output)) {
        perror("Error while writing to log"); 
        return -1; 
    }

    fclose(output);

    return 0;
}
