#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node* left;
    struct Node* right;
} Node;

Node* insert(Node* root, int val) {
    if (root == NULL) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->val = val;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }

    if (val < root->val) {
        root->left = insert(root->left, val);
    } else if (val > root->val) {
        root->right = insert(root->right, val);
    }

    return root;
}

void preOrder(Node* root) {
    if (root != NULL) {
        printf(" %d", root->val);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf(" %d", root->val);
        inOrder(root->right);
    }
}

void postOrder(Node* root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf(" %d", root->val);
    }
}

int countNodes(Node* root) {
    if (root == NULL) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int countLeaves(Node* root) {
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return 1;
    return countLeaves(root->left) + countLeaves(root->right);
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getHeight(Node* root) {
    if (root == NULL) return -1;
    return 1 + max(getHeight(root->left), getHeight(root->right));
}

int getMin(Node* root) {
    Node* current = root;
    while (current->left != NULL) {
        current = current->left;
    }
    return current->val;
}

int getMax(Node* root) {
    Node* current = root;
    while (current->right != NULL) {
        current = current->right;
    }
    return current->val;
}

void freeTree(Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    Node* root = NULL;
    int num;

    while (scanf("%d", &num) != EOF && num != -1) {
        root = insert(root, num);
    }

    if (root == NULL) {
        printf("ARVORE VAZIA\n");
        return 0;
    }

    printf("PREORDEM:");
    preOrder(root);
    printf("\n");

    printf("EMORDEM:");
    inOrder(root);
    printf("\n");

    printf("POSORDEM:");
    postOrder(root);
    printf("\n");


    printf("NOS: %d\n", countNodes(root));
    printf("FOLHAS: %d\n", countLeaves(root));
    printf("ALTURA: %d\n", getHeight(root));
    printf("MENOR: %d\n", getMin(root));
    printf("MAIOR: %d\n", getMax(root));


    freeTree(root);

    return 0;
}
