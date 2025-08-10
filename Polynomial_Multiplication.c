#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int coefficient;
    int exponent;
    struct Node* next;
} Node;

Node* createNode(int coefficient, int exponent) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->coefficient = coefficient;
    newNode->exponent = exponent;
    newNode->next = NULL;
    return newNode;
}

void insertNode(Node** head, int coefficient, int exponent) {
    Node* newNode = createNode(coefficient, exponent);
    if (*head == NULL || (*head)->exponent < exponent) {
        newNode->next = *head;
        *head = newNode;
    } else {
        Node* current = *head;
        while (current->next != NULL && current->next->exponent >= exponent) {
            current = current->next;
        }
        if (current->exponent == exponent) {
            current->coefficient += coefficient;
        } else {
            newNode->next = current->next;
            current->next = newNode;
        }
    }
}

Node* multiplyPolynomials(Node* poly1, Node* poly2) {
    Node* result = NULL;
    for (Node* p1 = poly1; p1 != NULL; p1 = p1->next) {
        for (Node* p2 = poly2; p2 != NULL; p2 = p2->next) {
            int coeff = p1->coefficient * p2->coefficient;
            int exp = p1->exponent + p2->exponent;
            insertNode(&result, coeff, exp);
        }
    }
    return result;
}

void printPolynomial(Node* poly) {
    while (poly != NULL) {
        printf("%dx^%d", poly->coefficient, poly->exponent);
        poly = poly->next;
        if (poly != NULL) {
            printf(" + ");
        }
    }
    printf("\n");
