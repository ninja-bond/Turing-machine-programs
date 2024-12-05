#include <stdio.h>
#include <string.h>

#define TAPE_LENGTH 200

typedef enum {
    START,
    SEARCH,
    REPLACE,
    MOVE,
    HALT
} State;

void search_and_replace(char *tape, const char *search, const char *replace) {
    State state = START;
    int head = 0;
    int search_len = strlen(search);
    int replace_len = strlen(replace);

    while (state != HALT) {
        switch (state) {
            case START:
                state = SEARCH;
                break;
            case SEARCH:
                if (strncmp(&tape[head], search, search_len) == 0) {
                    state = REPLACE;
                } else if (tape[head] == '\0') {
                    state = HALT;
                } else {
                    head++;
                }
                break;
            case REPLACE:
                if (replace_len <= search_len) {
                    strncpy(&tape[head], replace, replace_len);
                    memmove(&tape[head + replace_len], &tape[head + search_len], strlen(&tape[head + search_len]) + 1);
                } else {
                    memmove(&tape[head + replace_len], &tape[head + search_len], strlen(&tape[head + search_len]) + 1);
                    strncpy(&tape[head], replace, replace_len);
                }
                state = MOVE;
                break;
            case MOVE:
                head += replace_len;
                state = SEARCH;
                break;
            default:
                state = HALT;
                break;
        }
    }
}

int main() {
    char tape[TAPE_LENGTH];
    char search[50], replace[50];

    printf("Enter the input string: ");
    fgets(tape, TAPE_LENGTH, stdin);
    tape[strcspn(tape, "\n")] = '\0';

    printf("Enter the substring to search: ");
    fgets(search, 50, stdin);
    search[strcspn(search, "\n")] = '\0';

    printf("Enter the replacement substring: ");
    fgets(replace, 50, stdin);
    replace[strcspn(replace, "\n")] = '\0';

    search_and_replace(tape, search, replace);

    printf("Resulting string: %s\n", tape);

    return 0;
}
