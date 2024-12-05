#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAPE_LENGTH 100

typedef enum {
    START,
    ONES_COMPLEMENT,
    TWOS_COMPLEMENT,
    CARRY,
    HALT
} State;

void onesComp(char *tape) {
    State state = ONES_COMPLEMENT;
    int head = 0;

    while (state != HALT) {
        char current = tape[head];
        switch (state) {
            case ONES_COMPLEMENT:
                if (current == '1') {
                    tape[head] = '0';
                    head++;
                } else if (current == '0') {
                    tape[head] = '1';
                    head++;
                } else {
                    state = HALT;
                }
                break;
            default:
                state = HALT;
                break;
        }
    }
}

void twosComp(char *tape) {
    State state = TWOS_COMPLEMENT;
    int head = strlen(tape) - 1;

    while (state != HALT) {
        char current = tape[head];
        switch (state) {
            case TWOS_COMPLEMENT:
                if (current == '1') {
                    head--;
                } else if (current == '0') {
                    tape[head] = '1';
                    state = CARRY;
                } else if (head < 0) {
                    state = HALT;
                }
                break;
            case CARRY:
                if (head < 0 || tape[head] == '\0') {
                    state = HALT;
                } else if (tape[head] == '1') {
                    tape[head] = '0';
                    head--;
                } else if (tape[head] == '0') {
                    tape[head] = '1';
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

    printf("Enter a binary number: ");
    scanf("%s", tape);

    onesComp(tape);
    printf("1's Complement: %s\n", tape);

    printf("Enter the same binary number again: ");
    scanf("%s", tape);

    twosComp(tape);
    printf("2's Complement: %s\n", tape);

    return 0;
}
