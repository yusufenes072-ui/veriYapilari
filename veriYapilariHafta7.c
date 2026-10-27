
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

Node* createNode(int value) {
    Node *newNode = (Node*)malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("Bellek ayirma hatasi!\n");
        exit(1);
    }

    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

Node* insert(Node *root, int value) {
    if (root == NULL) {
        return createNode(value);
    }

    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    }

    return root;
}

int searchTreasure(Node *root, int target, int *steps) {
    if (root == NULL) {
        return 0;
    }

    (*steps)++;
    printf("Ziyaret edilen dugum: %d\n", root->data);

    if (root->data == target) {
        return 1;
    }

    if (target < root->data) {
        return searchTreasure(root->left, target, steps);
    } else {
        return searchTreasure(root->right, target, steps);
    }
}

void freeTree(Node *root) {
    if (root == NULL) {
        return;
    }

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(void) {
    Node *root = NULL;
    int n, value, target;
    int steps = 0;

    printf("Kac dugum eklenecek? ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Gecersiz dugum sayisi!\n");
        return 1;
    }

    printf("Agaca eklenecek sayilari girin:\n");

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &value) != 1) {
            freeTree(root);
            return 1;
        }

        root = insert(root, value);
    }

    printf("Aranacak hazine degerini girin: ");
    if (scanf("%d", &target) != 1) {
        freeTree(root);
        return 1;
    }

    printf("\nHazine araniyor...\n");

    if (searchTreasure(root, target, &steps)) {
        printf("\nHazine bulundu!\n");
    } else {
        printf("\nBosuna kazdin! Hazine bulunamadi.\n");
    }

    printf("Ziyaret edilen dugum sayisi: %d\n", steps);
    printf("En kotu durumdaki adim sayisi: %d\n", n);

    freeTree(root);

    return 0;
}

