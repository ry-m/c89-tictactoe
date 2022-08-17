#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "types.h"
#include "file_io.h"
#include "game.h"
#include "log.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: ./game [path-to-settings-file]\n");
        return -1; 
    } else {
        /* Check if the first argument is a readable file */
        if (access(argv[1], R_OK) == -1) {
            fprintf(stderr, "error: could not access file at '%s'\n", argv[1]);
        } else {
            /** File OK, read the settings */
            GameSettings* settings = (GameSettings*)malloc(sizeof(GameSettings)); 
            
            if (read_settings(settings, argv[1]) == -1) {
                fprintf(stderr, "error: failed to read settings file\n"); 
                return -1; 
            }

            launch_game(settings);

            /** Free memory */
            free(settings); 
        }
    }

    return 0; 
}
