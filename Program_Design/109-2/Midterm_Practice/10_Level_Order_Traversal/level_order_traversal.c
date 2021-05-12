#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NODE {
    char name[1024];
    struct NODE *left;
    struct NODE *right;
} Node;

typedef struct QUEUE {
    Node *arr[8192];
    int front, end, count;
} Queue;

Node *BST_newNode(char *key);
Node *BST_insert(Node *head, char *key);
void BST_preorder(Node *ptr);
void BST_inorder(Node *ptr);
void BST_postorder(Node *ptr);
void queue_init(Queue *s);
void queue_push(Queue *s, Node *n);
Node *queue_pop(Queue *s);
void BFS(Node *ptr);


//////////////////////////////////////////////////////////////////////
int main(int argc, char **argv) {
    Node *head = NULL;
    char buf[1024] = "";
    
    while (fgets(buf, 1024, stdin) != NULL) {
        if (buf[strlen(buf) - 1] == '\n') {
            buf[strlen(buf) - 1] =  '\0';
        }
        head = BST_insert(head, buf);
    }
    
    if (head != NULL) BFS(head);
    
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

void queue_init(Queue *s) {
    s->front = 0;
    s->end = 0;
    s->count = 0;
}

void queue_push(Queue *s, Node *n) {
    if (s->front - s->end == 8191 || s->front == s->end - 1) {
        fprintf(stderr, "overflow\n");
        return;
    }
    s->front = (s->front + 1) % 8192;
    s->arr[s->front] = n;
    ++(s->count);
}

Node *queue_pop(Queue *s) {
    if (s->front == s->end) {
        fprintf(stderr, "empty\n");
        return NULL;
    }
    s->end = (s->end + 1) % 8192;
    --(s->count);
    return s->arr[s->end];
    
}

void BFS(Node *ptr) {
    Queue s;
    Node *n;
    queue_init(&s);
    queue_push(&s, ptr);
    while (s.count > 0) {
        n = queue_pop(&s);
        printf("%s\n", n->name);
        if (n->left != NULL) queue_push(&s, n->left);
        if (n->right != NULL) queue_push(&s, n->right);
    }
}
