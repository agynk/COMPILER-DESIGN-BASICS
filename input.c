#include <stdio.h>
#include <ctype.h>
#include <string.h>

char keywords[][10] = {
    "int", "float", "char", "double", "if", "else", "while", "for", "return", "void"
};

int isKeyword(const char *word) {
    for (int i = 0; i < 10; i++) {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || 
            ch == '=' || ch == '<' || ch == '>' || ch == '!');
}

int main() {
    FILE *fp;
    char ch, buffer[100];
    int i = 0;

    fp = fopen("input.c", "r");

    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    printf("\n--- Lexical Analysis Output ---\n\n");

    while ((ch = fgetc(fp)) != EOF) {
        // Skip whitespaces
        if (isspace(ch)) continue;

        // Identifiers and Keywords
        if (isalpha(ch)) {
            buffer[i++] = ch;
            while (isalnum(ch = fgetc(fp)) || ch == '_') {
                buffer[i++] = ch;
            }
            buffer[i] = '\0';
            i = 0;
            ungetc(ch, fp);

            if (isKeyword(buffer))
                printf("%s --> Keyword\n", buffer);
            else
                printf("%s --> Identifier\n", buffer);
        }

        // Operators
        else if (isOperator(ch)) {
            char next = fgetc(fp);
            if ((ch == '=' && next == '=') || 
                (ch == '!' && next == '=') || 
                (ch == '<' && next == '=') || 
                (ch == '>' && next == '=')) {
                printf("%c%c --> Operator\n", ch, next);
            } else {
                ungetc(next, fp);
                printf("%c --> Operator\n", ch);
            }
        }

        // Ignore digits, delimiters, symbols for now
        else if (isdigit(ch)) {
            while (isdigit(ch = fgetc(fp)));
            ungetc(ch, fp); // skip numbers
        }
        else {
            // Ignore other symbols like ;, {}, (), etc.
        }
    }

    fclose(fp);
    return 0;
}
