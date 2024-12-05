#include <stdio.h>
#include <string.h>

#define TAPE_LENGTH 200

typedef enum {
    START,
    CHECK_FIRST,
    CHECK_SECOND,
    CHECK_THIRD,
    ACCEPT,
    REJECT
} State;

void recognizePattern(const char *pattern, char *tape) {
    State state = START;
    int head = 0;
    int patternIndex = 0;
    int patternLength = strlen(pattern);

    while (state != ACCEPT && state != REJECT) {
        switch (state) {
            case START:
                if (tape[head] == pattern[patternIndex]) {
                    state = CHECK_FIRST;
                    patternIndex++;
                    head++;
                } else if (tape[head] == '\0') {
                    state = REJECT;
                } else {
                    head++;
                }
                break;

            case CHECK_FIRST:
                if (tape[head] == pattern[patternIndex]) {
                    patternIndex++;
                    head++;
                    if (patternIndex == patternLength) {
                        state = ACCEPT;
                    } else {
                        state = CHECK_SECOND;
                    }
                } else {
                    patternIndex = 0;
                    state = START;
                }
                break;

            case CHECK_SECOND:
                if (tape[head] == pattern[patternIndex]) {
                    patternIndex++;
                    head++;
                    if (patternIndex == patternLength) {
                        state = ACCEPT;
                    } else {
                        state = CHECK_THIRD;
                    }
                } else {
                    patternIndex = 0;
                    state = START;
                }
                break;

            case CHECK_THIRD:
                if (tape[head] == pattern[patternIndex]) {
                    patternIndex++;
                    head++;
                    if (patternIndex == patternLength) {
                        state = ACCEPT;
                    }
                } else {
                    patternIndex = 0;
                    state = START;
                }
                break;

            default:
                state = REJECT;
                break;
        }
    }

    if (state == ACCEPT) {
        printf("The tape contains the pattern \"%s\".\n", pattern);
    } else {
        printf("The tape does not contain the pattern \"%s\".\n", pattern);
    }
}

int main() {
    char tape[TAPE_LENGTH];
    char pattern[50];

    printf("Enter the binary tape: ");
    fgets(tape, TAPE_LENGTH, stdin);
    tape[strcspn(tape, "\n")] = '\0';

    printf("Enter the binary pattern to recognize: ");
    fgets(pattern, 50, stdin);
    pattern[strcspn(pattern, "\n")] = '\0';

    recognizePattern(pattern, tape);

    return 0;
}
