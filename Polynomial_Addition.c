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

Node* addPolynomials(Node* poly1, Node* poly2) {
    Node* result = NULL;
    while (poly1 != NULL && poly2 != NULL) {
        if (poly1->exponent > poly2->exponent) {
            insertNode(&result, poly1->coefficient, poly1->exponent);
            poly1 = poly1->next;
        } else if (poly1->exponent < poly2->exponent) {
            insertNode(&result, poly2->coefficient, poly2->exponent);
            poly2 = poly2->next;
        } else {
            int sumCoefficient = poly1->coefficient + poly2->coefficient;
            if (sumCoefficient != 0) {
                insertNode(&result, sumCoefficient, poly1->exponent);
            }
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }

    while (poly1 != NULL) {
        insertNode(&result, poly1->coefficient, poly1->exponent);
        poly1 = poly1->next;
    }

    while (poly2 != NULL) {
        insertNode(&result, poly2->coefficient, poly2->exponent);
        poly2 = poly2->next;
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
}

int main() {
    Node* poly1 = NULL;
    Node* poly2 = NULL;

    insertNode(&poly1, 3, 4);
    insertNode(&poly1, 2, 3);
    insertNode(&poly1, 1, 0);

    insertNode(&poly2, 4, 3);
    insertNode(&poly2, 3, 2);
    insertNode(&poly2, 2, 1);
    insertNode(&poly2, 1, 0);

    printf("First polynomial: ");
    printPolynomial(poly1);

    printf("Second polynomial: ");
    printPolynomial(poly2);

    Node* result = addPolynomials(poly1, poly2);
    printf("Resultant polynomial: ");
    printPolynomial(result);

    return 0;
}
