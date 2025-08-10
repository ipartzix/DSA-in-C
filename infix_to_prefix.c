#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100
typedef struct {
    char items[MAX];
    int top;
} CharStack;
void initCharStack(CharStack* stack) {
    stack->top = -1;
}
int isCharStackEmpty(CharStack* stack) {
    return stack->top == -1;
}
int isCharStackFull(CharStack* stack) {
    return stack->top == MAX - 1;
}
void pushChar(CharStack* stack, char value) {
    if (isCharStackFull(stack)) {
        printf("Stack overflow!\n");
        exit(1);
    }
    stack->items[++stack->top] = value;
}

char popChar(CharStack* stack) {
    if (isCharStackEmpty(stack)) {
        printf("Stack underflow!\n");
        exit(1);
    }
    return stack->items[stack->top--];
}
char peekChar(CharStack* stack) {
    if (isCharStackEmpty(stack)) {
        return '\0';
    }
    return stack->items[stack->top];
}
int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    } else if (op == '*' || op == '/') {
        return 2;
    } else if (op == '^') {
        return 3;
    } else {
        return 0;
    }
}
int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}
void reverseString(char* str) {
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
    }
}

void infixToPrefix(char* infix, char* prefix) {
    CharStack stack;
    initCharStack(&stack);
    
    reverseString(infix);

    int k = 0;
    for (int i = 0; i < strlen(infix); i++) {
        char ch = infix[i];

        if (isalnum(ch)) {
            prefix[k++] = ch;
        } else if (ch == ')') {
            pushChar(&stack, ch);
        } else if (ch == '(') {
            while (!isCharStackEmpty(&stack) && peekChar(&stack) != ')') {
                prefix[k++] = popChar(&stack);
            }
            popChar(&stack);
        } else if (isOperator(ch)) {
            while (!isCharStackEmpty(&stack) && precedence(peekChar(&stack)) >= precedence(ch)) {
                prefix[k++] = popChar(&stack);
            }
            pushChar(&stack, ch);
        }
    }

    while (!isCharStackEmpty(&stack)) {
        prefix[k++] = popChar(&stack);
    }

    prefix[k] = '\0';
    reverseString(prefix);
}

int main() {
    char infix[MAX], prefix[MAX];

    printf("Enter an infix expression: ");
    scanf("%s", infix);

    infixToPrefix(infix, prefix);

    printf("Prefix expression: %s\n", prefix);

    return 0;
}