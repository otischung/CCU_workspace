#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NODE {
    char name[64];
    struct NODE *left;
    struct NODE *right;
} Node;

Node *BST_newNode(char *key);
Node *BST_insert(Node *head, char *key);
void BST_preorder(Node *ptr);
void BST_inorder(Node *ptr);
void BST_postorder(Node *ptr);


//////////////////////////////////////////////////////////////////////
int main(int argc, char **argv) {
    Node *head = NULL;
    char buf[64] = "";
    
    if (argc != 2) {
        fprintf(stderr, "format error\n");
        fprintf(stderr, "%s <-pPin\n", argv[0]);
        exit(1);
    }
    
    while (~scanf("%s", buf)) {
        head = BST_insert(head, buf);
    }
    
    if (!strcmp("-p", argv[1])) {
        BST_preorder(head);
    } else if (!strcmp("-P", argv[1])) {
        BST_postorder(head);
    } else if (!strcmp("-i", argv[1])) {
        BST_inorder(head);
    } else {
        fprintf(stderr, "format error\n");
        fprintf(stderr, "%s <-pPi>", argv[0]);
        exit(1);
    }
    
    return 0;
}
//////////////////////////////////////////////////////////////////////


Node *BST_newNode(char *key) {
    Node *newNode;
    
    newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->name, key);
    newNode->left = NULL;
    newNode->right = NULL;
    
    return newNode;
}

Node *BST_insert(Node *head, char *key) {
    Node *traverse;
    
    if (head == NULL) {
        traverse = BST_newNode(key);
        return traverse;
    }
    
    traverse = head;
    
    if (!strcmp(traverse->name, key)) {
        return head;
    }
    
    if (strcmp(key, traverse->name) < 0) {
        if (traverse->left == NULL) {
            traverse->left = BST_newNode(key);
        } else {
            BST_insert(traverse->left, key);
        }
    } else {
        if (traverse->right == NULL) {
            traverse->right = BST_newNode(key);
        } else {
            BST_insert(traverse->right, key);
        }
    }
    
    return head;
}

void BST_preorder(Node *ptr) {
    printf("%s\n", ptr->name);
    if (ptr->left != NULL) BST_preorder(ptr->left);
    if (ptr->right != NULL) BST_preorder(ptr->right);
}

void BST_inorder(Node *ptr) {
    if (ptr->left != NULL) BST_inorder(ptr->left);
    printf("%s\n", ptr->name);
    if (ptr->right != NULL) BST_inorder(ptr->right);
}

void BST_postorder(Node *ptr) {
    if (ptr->left != NULL) BST_postorder(ptr->left);
    if (ptr->right != NULL) BST_postorder(ptr->right);
    printf("%s\n", ptr->name);
}
