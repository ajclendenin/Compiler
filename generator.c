#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "not enough arguments\n");
        return 1;
    }

    // output file: input name with its extension replaced by .s
    char outpath[256];
    snprintf(outpath, sizeof(outpath) - 2, "%s", argv[1]);
    char *dot = strrchr(outpath, '.');
    if (dot != NULL && strchr(dot, '/') == NULL) *dot = '\0';
    strcat(outpath, ".s");

    FILE *input = fopen(argv[1], "r");
    if (input == NULL) {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        return 1;
    }
    FILE *output = fopen(outpath, "w");
    if (output == NULL) {
        fprintf(stderr, "Error creating file: %s\n", outpath);
        fclose(input);
        return 1;
    }

    fprintf(output, "    .text\n");

    char line[256];
    int lineno = 0;
    const char *error = NULL;
    while (error == NULL && fgets(line, sizeof(line), input) != NULL) {
        lineno++;

        // split "name : expression"
        char *colon = strchr(line, ':');
        if (colon != NULL) *colon = '\0';
        char *name = strtok(line, " \t\r\n");
        if (name == NULL && colon == NULL) continue;    // blank line
        if (name != NULL && name[0] == '#') continue;   // comment
        if (name == NULL || colon == NULL) {
            error = "expected 'name : expression'";
            break;
        }

        fprintf(output, "\n    .global %s\n%s:\n", name, name);
        fprintf(output, "    push %%ebp\n");
        fprintf(output, "    mov  %%esp, %%ebp\n");

        // each value is pushed on the CPU stack; the stack module tracks how many there will be
        char *params[128];   // a 256-character line can't hold more tokens than this
        int nparams = 0;
        clear();
        for (char *tok = strtok(colon + 1, " \t\r\n"); tok != NULL; tok = strtok(NULL, " \t\r\n")) {
            if (strlen(tok) == 1 && strchr("+-*/", tok[0]) != NULL) {
                // takes two values and leaves one: pop one, the other stands for the result
                if (is_empty()) { error = "not enough values"; break; }
                pop();
                if (is_empty()) { error = "not enough values"; break; }

                fprintf(output, "    popl  %%ecx\n");   // right operand
                fprintf(output, "    popl  %%eax\n");   // left operand
                if (tok[0] == '+') {
                    fprintf(output, "    addl  %%ecx, %%eax\n");
                } else if (tok[0] == '-') {
                    fprintf(output, "    subl  %%ecx, %%eax\n");
                } else if (tok[0] == '*') {
                    fprintf(output, "    imull %%ecx, %%eax\n");
                } else {
                    fprintf(output, "    cltd\n");          // sign-extend %eax into %edx:%eax
                    fprintf(output, "    idivl %%ecx\n");
                }
                fprintf(output, "    pushl %%eax\n");
            } else if (isdigit((unsigned char)tok[0])) {
                fprintf(output, "    pushl $%s\n", tok);
                push(tok);
            } else if (isalpha((unsigned char)tok[0]) || tok[0] == '_') {
                // parameters are numbered in order of first appearance;
                // the caller pushed them above the return address, starting at 8(%ebp)
                int i = 0;
                while (i < nparams && strcmp(params[i], tok) != 0) i++;
                if (i == nparams) params[nparams++] = tok;
                fprintf(output, "    pushl %d(%%ebp)\n", 8 + 4 * i);
                push(tok);
            } else {
                error = "invalid token";
                break;
            }
        }

        if (error == NULL) {
            if (is_empty()) {
                error = "empty expression";
            } else {
                pop();
                if (!is_empty()) error = "more than one value remains";
            }
        }
        if (error == NULL) {
            fprintf(output, "    popl  %%eax\n");   // result is returned in %eax
            fprintf(output, "    leave\n");         // restore %esp and %ebp
            fprintf(output, "    ret\n");
        }
    }

    fclose(input);
    fclose(output);

    if (error != NULL) {
        fprintf(stderr, "%s:%d: %s\n", argv[1], lineno, error);
        remove(outpath);   // don't leave a partial .s behind
        return 1;
    }
    return 0;
}
