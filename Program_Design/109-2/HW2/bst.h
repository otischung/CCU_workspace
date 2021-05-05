#pragma once
#include "randint_gen.h"

typedef struct BSTNODE {
    int key;
    struct BSTNODE *left, *right;
} BSTNode;

static void binary_search_tree(int arrsize, int query);
static BSTNode *BSTNewNode(int key);
static BSTNode *BST_insert(BSTNode *head, int key);
static bool BST_find(BSTNode *head, int key);
static void BST_print_inorder(BSTNode *ptr);
static void BST_print_preorder(BSTNode *ptr);
static void BST_print_postorder(BSTNode *ptr);

///////////////////////////////////////////////////////////////////////////
static void binary_search_tree(int arrsize, int query) {
    FILE *fp;
    int num;
    struct timespec start, end;
    time_t diff;
    BSTNode *head = NULL;

    fp = fopen("./randint.txt", "r");
    if (fp == NULL) {
        perror("fopen error");
        exit(1);
    }
    printf("bst:\n");

    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < arrsize; ++i) {
        fscanf(fp, "%d", &num);
        head = BST_insert(head, num);
    }
    // head = BST_insert(head, 4);
    // head = BST_insert(head, 2);
    // head = BST_insert(head, 1);
    // head = BST_insert(head, 3);
    // head = BST_insert(head, 6);
    // head = BST_insert(head, 5);
    // head = BST_insert(head, 7);
    clock_gettime(CLOCK_MONOTONIC, &end);
    diff = (end.tv_sec - start.tv_sec) * 1000000000 + end.tv_nsec - start.tv_nsec;
    printf("Time for insert key to BST: %ldns = %.2lfs\n", diff, (double)diff / 1000000000.0);
    num = 0;
    
    // BST_print_inorder(head);
    // putchar('\n');
    // BST_print_preorder(head);
    // putchar('\n');
    // BST_print_postorder(head);
    // putchar('\n');

    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < query; ++i) {
        if (BST_find(head, rand())) {
            ++num;
        }
    }
    // BST_find(head, 1);
    // BST_find(head, 2);
    // BST_find(head, 3);
    // BST_find(head, 4);
    // BST_find(head, 5);
    // BST_find(head, 6);
    // BST_find(head, 7);
    clock_gettime(CLOCK_MONOTONIC, &end);
    diff = (end.tv_sec - start.tv_sec) * 1000000000 + end.tv_nsec - start.tv_nsec;
    printf("We have found %d keys.\n", num);
    printf("Time for search in BST: %ldns = %.2lfs\n\n", diff, (double)diff / 1000000000.0);

    fclose(fp);
}
///////////////////////////////////////////////////////////////////////////

static BSTNode *BSTNewNode(int key) {
    BSTNode *newNode = (BSTNode *)malloc(sizeof(BSTNode));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

static BSTNode *BST_insert(BSTNode *head, int key) {
    BSTNode *newNode;
    BSTNode *traverse;

    if (head == NULL) {
        newNode = BSTNewNode(key);
        return newNode;
    }

    traverse = head;
    if (traverse->key >= key) {
        if (traverse->left == NULL) {
            newNode = BSTNewNode(key);
            traverse->left = newNode;
        } else {
            BST_insert(traverse->left, key);
        }
    } else {
        if (traverse->right == NULL) {
            newNode = BSTNewNode(key);
            traverse->right = newNode;
        } else {
            BST_insert(traverse->right, key);
        }
    }
    return head;
}

static bool BST_find(BSTNode *head, int key) {
    BSTNode *traverse = head;
    if (traverse->key == key) {
        printf("%d is found.\n", key);
        return true;
    } else if (traverse->key >= key) {
        if (traverse->left != NULL) BST_find(traverse->left, key);
        else return false;
    } else {
        if (traverse->right != NULL) BST_find(traverse->right, key);
        else return false;
    }
}

static void BST_print_inorder(BSTNode *ptr) {
    if (ptr->left != NULL) BST_print_inorder(ptr->left);
    printf("%d\n", ptr->key);
    if (ptr->right != NULL) BST_print_inorder(ptr->right);
}

static void BST_print_preorder(BSTNode *ptr) {
    printf("%d\n", ptr->key);
    if (ptr->left != NULL) BST_print_preorder(ptr->left);
    if (ptr->right != NULL) BST_print_preorder(ptr->right);
}

static void BST_print_postorder(BSTNode *ptr) {
    if (ptr->left != NULL) BST_print_postorder(ptr->left);
    if (ptr->right != NULL) BST_print_postorder(ptr->right);
    printf("%d\n", ptr->key);
}