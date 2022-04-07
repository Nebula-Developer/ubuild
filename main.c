#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define red "\e[31m"
#define green "\e[32m"
#define yellow "\e[33m"
#define blue "\e[34m"
#define gray "\e[37m"

#define italic "\e[3m"
#define reset "\e[0m"


int runFunction(int index, int cap, char *seperator_name) {
    // Read each line of ubf until at index
    FILE *ubf = fopen("ubuild", "r");
    printf("%s%sRunning Seperator '%s'%s\n\n", gray, italic, seperator_name, reset);

    char *subl = NULL;
    size_t len = 0;
    ssize_t read;
    int infunc = 0;
    int curline = 0;

    // Multiply " " by cap into char pointer
    char *space = malloc(sizeof(char) * cap);
    memset(space, ' ', cap);

    // Start line loop
    while ((read = getline(&subl, &len, ubf)) != -1) {
        subl[strcspn(subl, "\n")];
        char line[1000];

        // Set line to the current line 
        strcpy(line, subl);
        line[strcspn(line, "\n")] = 0;
        curline++;

        for (int i = 0; i < strlen(line); i++) {

            if (line[i] == '\t') {
                // Set temp char array to %s%s, space, line
                char *old = line;
                char *temp = malloc(sizeof(char) * (strlen(line) + strlen(space) + 1));
                sprintf(temp, "%s%s", space, line + i + 1);

                // Set line array to temp
                strcpy(line, temp);

                for (int j = 0; j < strlen(line); j++) {
                    if(line[i] == '\t') {
                        printf("Fatal: Failed to copy tab spaces.\n");
                        return -1;
                    }
                }
            }
        }

        if (!(curline >= (index + 2)) || strlen(line) == 0) {
            continue;
        }

        char *operation = strndup(line + cap, strlen(line));

        if (strcmp(strndup(line, 3), "sep") != 0) {
            printf("%s%s%s%s\n", gray, italic, operation, reset);
        } else {
            printf("%sSeperator Ended.%s\n", yellow, reset);
        }

        if (strcmp(strndup(line, cap), space) != 0 || strcmp(strndup(line + cap, 1), " ") == 0) {
            if(strcmp(strndup(line + cap, strlen(line)), seperator_name) != 0) {
                return 0;
            } else {
                continue;
            }
        }

        
        system(operation);
    }
}

int main(int argc, char **argv) {
    FILE *ubf = fopen("ubuild", "r");
    if (ubf == NULL) {
        printf("Error: ubuild file not found\n");
        return 1;
    }
    
    char *subl = NULL;
    size_t len = 0;
    ssize_t read;
    int infunc = 0;
    int curline = 0;

    int chose_first = 0;

    int cap = 4;
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-c") == 0) {
            if (argc > (i + 1)) {
                cap = atoi(argv[i + 1]);
                printf("Cap: %d\n", cap);
            } else {
                printf("Error: -c requires an argument\n");
                return 1;
            }
        }
    }

    while ((read = getline(&subl, &len, ubf)) != -1) {
        subl[strcspn(subl, "\n")];
        char line[1000];

        // Set line to the current line 
        strcpy(line, subl);
        line[strcspn(line, "\n")] = 0;

        // Check if no seperator argument was defined, then use the first option.
        char *seperator = strndup(line, 3);
        char *seperator_name = strndup(line + 4, strlen(line));

        char *space = malloc(sizeof(char) * cap);
        memset(space, ' ', cap);


        if (strlen(line) == 0)
            continue;

        for (int i = 0; i < strlen(line); i++) {
            if (line[i] == '\t') {
                // Set temp char array to %s%s, space, line
                char *old = line;
                char *temp = malloc(sizeof(char) * (strlen(line) + strlen(space) + 1));
                sprintf(temp, "%s%s", space, line + i + 1);


                


                // Set line array to temp
                strcpy(line, temp);

                for (int j = 0; j < strlen(line); j++) {
                    if(line[i] == '\t') {
                        printf("Fatal: Failed to copy tab spaces.\n");
                        return -1;
                    }
                }
            }
        }

        if (argc < 2 && strcmp(seperator, "sep") == 0 && chose_first == 0) {
            runFunction(curline, cap, seperator_name);
            chose_first = 1;
            infunc = 1;
        } else if (strcmp(seperator, "sep") == 0) {
            if (!chose_first == 1) {
                for (int b = 1; b < argc; b++) {
                    if (strcmp(seperator_name, argv[b]) == 0) {
                        infunc = 1;
                        runFunction(curline, cap, seperator_name);
                    }
                }
            }
        } else if (strcmp(strndup(line, cap), space) != 0) {
            printf("%sInvalid function at: ..%s%s\n", red, line, reset);
            printf("%s                       ^ %s\n", green, reset);

            printf("\nUBuild syntax error at line %d\n", curline);
            return -1;
        }

        curline++;
    }

    if (infunc == 0 && argc >= 2) {
        printf("Error: Invalid seperator defined.\n");
        return 1;
    } else if (infunc == 0) {
        printf("Error: No seperators found.\n");
        return 1;
    }
} 