#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
/**************** BEGIN VECTOR ****************/
#ifndef VECTOR
#define VECTOR
#define vector(identifier) struct vector_##identifier
#define vector_register(type, identifier) \
    vector(identifier) {                  \
        int cap;                          \
        int len;                          \
        type *arr;                        \
    }
#define vector_init(type, identifier) \
    (vector(identifier)) { .cap = 0, .len = 0, .arr = NULL }
#define vector_destory(v, callback)                             \
    do {                                                        \
        for (int i = 0; i < v.len; i++) (callback)((v).arr[i]); \
        free((v).arr);                                          \
    } while (0)
#define vector_push(v, val)                                                     \
    do {                                                                        \
        if ((v).cap < (v).len + 2) {                                            \
            (v).arr = realloc((v).arr, sizeof(*((v).arr)) * 2 * ((v).cap + 1)); \
            assert((v).arr != NULL);                                            \
            (v).cap = 2 * ((v).cap + 1);                                        \
        }                                                                       \
        (v).arr[(v).len++] = (val);                                             \
    } while (0)

#endif
/***************** END VECTOR *****************/

#ifndef VECTOR_INT
#define VECTOR_INT
vector_register(int, int);
struct node_dat {
    int dest;
    int weight;
};
struct node {
    int parent;
    int id;
    int weight;
    vector(int) children;
};

/***************** begin heap *****************/

struct heap {
    int idx;
    struct node nodes[100000];
};
struct heap heap_init() {
    return (struct heap){.idx = 0};
};
static inline int heap_left(int i) { return 2 * i + 1; }
static inline int heap_right(int i) { return 2 * i + 2; }
static inline int heap_parent(int i) {
    assert(i > 0);
    return (i - 1) / 2;
}

#define swap(a, b)         \
    do {                   \
        typeof(b) tmp = b; \
        b = a;             \
        a = tmp;           \
    } while (0)

void heap_filter_down(struct heap *heap, int i) {
    if (i * 2 + 1 >= heap->idx) return;
    if (heap->nodes[i].weight < heap->nodes[heap_left(i)].weight && heap->nodes[i].weight < heap->nodes[heap_right(i)].weight) return;
    if (heap->nodes[heap_left(i)].weight < heap->nodes[heap_right(i)].weight) {
        swap(heap->nodes[i], heap->nodes[heap_left(i)]);
        heap_filter_down(heap, heap_left(i));
    } else {
        swap(heap->nodes[i], heap->nodes[heap_right(i)]);
        heap_filter_down(heap, heap_right(i));
    }
}

struct node heap_pop(struct heap *heap) {
    assert(heap->idx > 0);
    struct node r = heap->nodes[0];
    if (heap->idx == 1) {
        heap->idx = 0;
        return r;
    }
    heap->idx--;
    heap->nodes[0] = heap->nodes[heap->idx];
    int i = 0;
    while (i * 2 + 1 < heap->idx) {
        if (heap->nodes[i].weight < heap->nodes[heap_left(i)].weight && heap->nodes[i].weight < heap->nodes[heap_right(i)].weight) break;
        if (heap->nodes[heap_left(i)].weight < heap->nodes[heap_right(i)].weight) {
            swap(heap->nodes[i], heap->nodes[heap_left(i)]);
            i = heap_left(i);
        } else {
            swap(heap->nodes[i], heap->nodes[heap_right(i)]);
            i = heap_right(i);
        }
    }
    // heap_filter_down(heap, 0);
    return r;
}

void heap_push(struct heap *heap, struct node node) {
    int i = heap->idx;
    while (i > 0 && heap->nodes[heap_parent(i)].weight > node.weight) {
        heap->nodes[i].weight = heap->nodes[heap_parent(i)].weight;
        i = heap_parent(i);
    }
    heap->nodes[i] = node;
    heap->idx++;
}

/***************** end heap *****************/

vector_register(struct node, node);
int weights[1000000];
int vis[1000000];
vector(int) nodes[10000000];
struct node history[1000000];
#endif

// ret: sum of weights until node_id
int dfs(int node_id, int pkg_size, int *cost) {
    struct node n = history[node_id];
    int sum = weights[node_id];
    for (int i = 0; i < n.children.len; i++) {
        sum += dfs(n.children.arr[i], pkg_size, cost);
    }
    if (node_id != 0) {
        *cost += (sum + pkg_size - 1) / pkg_size;
    }
    return sum;
}
void dfs_output(int node_id) {
    struct node n = history[node_id];
    for (int i = 0; i < n.children.len; i++) {
        printf("%d %d\n", n.children.arr[i], node_id);
        dfs_output(n.children.arr[i]);
    }
}
int main() {
    int n_nodes, n_path, p_size;
    scanf("%d %d %d", &n_nodes, &n_path, &p_size);
    for (int i = 0; i < n_nodes; i++) {
        nodes[i] = vector_init(int, int);
        history[i].children = vector_init(int, int);
        int idx, tmp;
        scanf("%d %d", &idx, &tmp);
        weights[idx] = tmp;
    }

    for (int i = 0; i < n_path; i++) {
        int tmp, p, q;
        scanf("%d %d %d", &tmp, &p, &q);
        vector_push(nodes[p], q);
        vector_push(nodes[q], p);
    }
    struct heap heap = heap_init();
    heap_push(&heap, (struct node){.children = vector_init(int, int), .weight = 0, .parent = -1});
    while (heap.idx > 0) {
        struct node top = heap_pop(&heap);
        if (vis[top.id]) {
            continue;
        }
        if (top.parent != -1) {
            vector_push(history[top.parent].children, top.id);
        }

        vis[top.id] = 1;
        for (int i = 0; i < nodes[top.id].len; i++) {
            if (vis[nodes[top.id].arr[i]]) continue;
            heap_push(&heap, (struct node){.children = vector_init(int, int), .id = nodes[top.id].arr[i], .parent = top.id, .weight = weights[nodes[top.id].arr[i]] + top.weight});
        }

        history[top.id] = top;
    }
    int cost = 0;
    dfs(0, p_size, &cost);
    printf("##### %d %d\n", n_nodes, cost);
    dfs_output(0);
    for (int i = 0; i < n_nodes; i++) {
        vector_destory(history[i].children, void);
        vector_destory(nodes[i], void);
    }
}
