#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 100
typedef struct {
    int top;
    char items[MAX];
} Stack;
void initStack(Stack* s) {
    s->top = -1;
}
int isFull(Stack* s) {
    return s->top == MAX - 1;
}
int isEmpty(Stack* s) {
    return s->top == -1;
}
void push(Stack* s, char item) {
    if (isFull(s)) {
        printf("Stack Overflow\n");
        return;
    }
    s->items[++s->top] = item;
}
char pop(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack Underflow\n");
        return '\0';
    }
    return s->items[s->top--];
}
char peek(Stack* s) {
    if (isEmpty(s)) {
        return '\0';
    }
    return s->items[s->top];
}
int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}
void infixToPostfix(const char* infix, char* postfix) {
    Stack s;
    initStack(&s);
    int k = 0;
    for (int i = 0; infix[i] != '\0'; i++) {
        if (isdigit(infix[i]) || isalpha(infix[i])) {
            postfix[k++] = infix[i];
        } else if (infix[i] == '(') {
            push(&s, infix[i]);
        } else if (infix[i] == ')') {
            while (!isEmpty(&s) && peek(&s) != '(') {
                postfix[k++] = pop(&s);
            }
            pop(&s);  // Remove '(' from stack
        } else {
            while (!isEmpty(&s) && precedence(peek(&s)) >= precedence(infix[i])) {
                postfix[k++] = pop(&s);
            }
            push(&s, infix[i]);
        }
    }
    while (!isEmpty(&s)) {
        postfix[k++] = pop(&s);
    }
    postfix[k] = '\0';
}
int main() {
    char infix[MAX], postfix[MAX];
    printf("Enter an infix expression: ");
    scanf("%s", infix);
    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);
    return 0;
}