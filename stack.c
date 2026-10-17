#include "stack.h"
#include <stddef.h>

#define MAX_CAPACITY 100
static char *data[MAX_CAPACITY];
static int top = -1;

void push(char *x) {
    if (top < MAX_CAPACITY - 1) {
        top++;
        data[top] = x;
    }
}

char *pop() {
    if (top >= 0) {
        char *value = data[top];
        top--;
        return value;
    }
    return NULL; 
}

int is_empty() {
    return top == -1;
}

void clear() {
    top = -1;
}
