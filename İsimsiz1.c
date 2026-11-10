#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int height(struct Node* node) {
    int leftHeight;
    int rightHeight;
    if (node == NULL)
        return 0;
    leftHeight = height(node->left);
    rightHeight = height(node->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int balanceFactor(struct Node* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

struct Node* insertBST(struct Node* root, int data) {
    if (root == NULL)
        return createNode(data);
    if (data < root->data)
        root->left = insertBST(root->left, data);
    else if (data > root->data)
        root->right = insertBST(root->right, data);
    return root;
}

struct Node* rotateLeft(struct Node* x) {
    struct Node* y = x->right;
    struct Node* t2 = y->left;

    y->left = x;
    x->right = t2;

    return y;
}

void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void preorder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

int main() {
    struct Node* root = NULL;
    int values[] = {10, 20, 30};
    int i;
    int bf;

    for (i = 0; i < 3; i++) {
        root = insertBST(root, values[i]);
        bf = balanceFactor(root);
        printf("%d eklendi. BF(kok) = %d\n", values[i], bf);

        if (bf < -1) {
            printf("RR dengesizligi: Sol rotasyon!\n\n");
            root = rotateLeft(root);
        }
    }

    printf("Kok: %d\n", root->data);

    printf("Inorder: ");
    inorder(root);
    printf("\n");

    printf("Preorder: ");
    preorder(root);
    printf("\n");

    return 0;
}
