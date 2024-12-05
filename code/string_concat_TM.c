#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAPE_LENGTH 200

typedef enum {
    START,
    FIND_END,
    APPEND,
    HALT
} State;

void concatenate(char *tape, const char *str2) {
    State state = START;
    int head = 0;
    int i = 0;

    while (state != HALT) {
        switch (state) {
            case START:
                state = FIND_END;
                break;
            case FIND_END:
                if (tape[head] == '\0') {
                    state = APPEND;
                } else {
                    head++;
                }
                break;
            case APPEND:
                if (str2[i] != '\0') {
                    tape[head] = str2[i];
                    head++;
                    i++;
                } else {
                    tape[head] = '\0';
                    state = HALT;
                }
                break;
            default:
                state = HALT;
                break;
        }
    }
}

int main() {
    char tape[TAPE_LENGTH];
    char str2[TAPE_LENGTH];

    printf("Enter the first string: ");
    fgets(tape, TAPE_LENGTH, stdin);
    tape[strcspn(tape, "\n")] = '\0';

    printf("Enter the second string: ");
    fgets(str2, TAPE_LENGTH, stdin);
    str2[strcspn(str2, "\n")] = '\0';

    concatenate(tape, str2);
    printf("Concatenated string: %s\n", tape);

    return 0;
}
