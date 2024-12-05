#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TAPE_LENGTH 200

typedef enum {
    START,
    PARSE_SUBJECT,
    PARSE_VERB,
    PARSE_OBJECT,
    ACCEPT,
    REJECT
} State;

void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

int isSubject(const char *word) {
    return strcmp(word, "i") == 0;
}

int isVerb(const char *word) {
    return strcmp(word, "eat") == 0 || strcmp(word, "like") == 0;
}

int isObject(const char *word) {
    return strcmp(word, "apple") == 0 || strcmp(word, "pizza") == 0;
}

void parseSentence(char *tape) {
    State state = START;
    char *token = strtok(tape, " ");
    int position = 0;

    while (state != ACCEPT && state != REJECT) {
        switch (state) {
            case START:
                if (token != NULL && isSubject(token)) {
                    state = PARSE_SUBJECT;
                } else {
                    state = REJECT;
                }
                break;

            case PARSE_SUBJECT:
                token = strtok(NULL, " ");
                if (token != NULL && isVerb(token)) {
                    state = PARSE_VERB;
                } else {
                    state = REJECT;
                }
                break;

            case PARSE_VERB:
                token = strtok(NULL, " ");
                if (token != NULL && isObject(token)) {
                    state = PARSE_OBJECT;
                } else {
                    state = REJECT;
                }
                break;

            case PARSE_OBJECT:
                token = strtok(NULL, " ");
                if (token == NULL) {
                    state = ACCEPT;
                } else {
                    state = REJECT;
                }
                break;

            default:
                state = REJECT;
                break;
        }
        position++;
    }

    if (state == ACCEPT) {
        printf("The sentence is valid.\n");
    } else {
        printf("The sentence is invalid.\n");
    }
}

int main() {
    char tape[TAPE_LENGTH];

    printf("Enter a sentence: ");
    fgets(tape, TAPE_LENGTH, stdin);
    tape[strcspn(tape, "\n")] = '\0';

    toLowerCase(tape);

    parseSentence(tape);

    return 0;
}
