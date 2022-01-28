#pragma GCC optimize("O3")
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#define A_LARGE_NUM 1048576  // 2^20

#define swap(a, b)          \
    do {                    \
        typeof(a) temp = a; \
        a = b;              \
        b = temp;           \
    } while (0)

/* ======================== VECTOR START ======================== */
#define vector(name) struct vector_##name  // ## means substitution

#define vector_declare(type, name) \
    vector(name) {                 \
        type *arr;                 \
        int capacity;              \
        int length;                \
    }

#define vector_init(v, type)                      \
    do {                                          \
        v.length = 0;                             \
        v.capacity = 4;                           \
        v.arr = (type *)malloc(4 * sizeof(type)); \
        if (v.arr == NULL) {                      \
            perror("vector init");                \
            abort();                              \
        }                                         \
    } while (0)

#define vector_push(v, val)                                                \
    do {                                                                   \
        if ((v).length == (v).capacity) {                                  \
            (v).capacity <<= 1;                                            \
            (v).arr = realloc((v).arr, (v).capacity * sizeof(*((v).arr))); \
            if ((v).arr == NULL) {                                         \
                perror("realloc failed");                                  \
                abort();                                                   \
            }                                                              \
        }                                                                  \
        (v).arr[(v).length++] = (val);                                     \
    } while (0)

#define vector_dump(v, dump_fn)                                         \
    do {                                                                \
        for (int i = 0; i < v.length; ++i) {                            \
            dump_fn(v.arr[i]);                                          \
        }                                                               \
        printf("\nlength = %d\ncapacity = %d\n", v.length, v.capacity); \
    } while (0)

#define vector_free(v) \
    do {               \
        free((v).arr); \
    } while (0)

/* ------------------------- VECTOR END ------------------------- */

vector_declare(int, int);  // struct vector_int { int *arr; int capacity; int length; };
typedef struct NODE {      // A tree builded when traverse each node.
    int id;
    int weight;
    int parent;
    vector(int) children;
} Node;

vector_declare(Node, Node);  // struct vector_Node { Node *arr; int capacity; int length; };

/* ========================= HEAP START ========================= */

typedef struct HEAP {
    int length;
    vector(Node) arr;
} Heap;

static inline int heap_left(int i) { return 2 * i + 1; }
static inline int heap_right(int i) { return 2 * i + 2; }
static inline int heap_parent(int i) { return (i - 1) / 2; }  // May be a negative number

#define heap_init(h, type)                 \
    do {                                   \
        /* type must impl .weight field */ \
        type a = (type){.weight = 0};      \
        h.length = 0;                      \
        vector_init(h.arr, type);          \
    } while (0)

#define heap_free(h)        \
    do {                    \
        vector_free(h.arr); \
    } while (0)

#define heap_push(heap, node)                                                  \
    do {                                                                       \
        vector_push(heap.arr, (node));                                         \
        int i = heap.length;                                                   \
        /* len > 0 provides parent is an nonnegative number*/                  \
        while (i > 0 && heap.arr.arr[heap_parent(i)].weight > (node).weight) { \
            swap(heap.arr.arr[i], heap.arr.arr[heap_parent(i)]);               \
            i = heap_parent(i);                                                \
        }                                                                      \
        ++(heap.length);                                                       \
    } while (0)

#define heap_pop(heap)                                                                                                                                \
    heap.arr.arr[0];                                                                                                                                  \
    do {                                                                                                                                              \
        if (!heap.length) {                                                                                                                           \
            fprintf(stderr, "heap %p is empty\n", &heap);                                                                                             \
            abort();                                                                                                                                  \
        }                                                                                                                                             \
        if (heap.length) {                                                                                                                            \
            --(heap.length);                                                                                                                          \
            --(heap.arr.length);                                                                                                                      \
            heap.arr.arr[0] = heap.arr.arr[heap.length];                                                                                              \
            int i = 0;                                                                                                                                \
            while (i * 2 + 1 < heap.length) {                                                                                                         \
                if (heap.arr.arr[i].weight < heap.arr.arr[heap_left(i)].weight && heap.arr.arr[i].weight < heap.arr.arr[heap_right(i)].weight) break; \
                if (heap.arr.arr[heap_left(i)].weight < heap.arr.arr[heap_right(i)].weight) {                                                         \
                    swap(heap.arr.arr[i], heap.arr.arr[heap_left(i)]);                                                                                \
                    i = heap_left(i);                                                                                                                 \
                } else {                                                                                                                              \
                    swap(heap.arr.arr[i], heap.arr.arr[heap_right(i)]);                                                                               \
                    i = heap_right(i);                                                                                                                \
                }                                                                                                                                     \
            }                                                                                                                                         \
        }                                                                                                                                             \
    } while (0)

/* -------------------------- HEAP END -------------------------- */

void node_dump(Node n) {
    printf("%d\n", n.weight);
}

int weights[A_LARGE_NUM];
int visited[A_LARGE_NUM];
vector(int) nodes[A_LARGE_NUM];
vector(int) tree[A_LARGE_NUM];
int cost = 0;

/* ========================= DFS START ========================== */
int dfs(int idx, int p_size) {
    int sum = weights[idx];
    for (int i = 0; i < tree[idx].length; ++i) {
        sum += dfs(tree[idx].arr[i], p_size);
    }
    if (idx) {
        cost += (sum + p_size - 1) / p_size;
    }
    return sum;
}
/* -------------------------- DFS END --------------------------- */

int cmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

int main() {
    int n_nodes, n_path, p_size;
    int idx, weight;
    int end1, end2;
    Heap heap;
    Node n;
    vector(int) v;
    int *result;

    scanf("%d %d %d", &n_nodes, &n_path, &p_size);
    for (int i = 0; i < n_nodes; ++i) {  // scanf node weight
        vector_init(nodes[i], int);
        vector_init(tree[i], int);
        scanf("%d %d", &idx, &weight);
        weights[idx] = weight;
    }

    for (int i = 0; i < n_path; ++i) {  // scanf link end and build graph.
        scanf("%d %d %d", &idx, &end1, &end2);
        vector_push(nodes[end1], end2);
        vector_push(nodes[end2], end1);
    }
    ///////////////////////////////////////

    heap_init(heap, Node);
    heap_push(heap, ((Node){.id = 0, .parent = -1}));
    while (heap.length > 0) {
        Node top = heap_pop(heap);
        if (visited[top.id]) {
            continue;
        }
        visited[top.id] = 1;
        if (top.parent != -1) {
            vector_push(tree[top.parent], top.id);
        }
        for (int i = 0; i < nodes[top.id].length; ++i) {
            // n = (Node){.id = nodes[top.id].arr[i], .parent = top.id, .weight = weights[top.id] % p_size};
            n = (Node){.id = nodes[top.id].arr[i], .parent = top.id, .weight = weights[top.id]};
            // n = (Node){.id = nodes[top.id].arr[i], .parent = top.id, .weight = 0};  // .weight = 0 means BFS
            heap_push(heap, n);
        }
    }
    dfs(0, p_size);
    printf("%d %d\n", n_nodes, cost);
    printf("0 0\n");
    result = (int *)malloc(n_nodes * sizeof(int));
    for (int i = 0; i < n_nodes; ++i) {
        for (int j = 0; j < tree[i].length; ++j) {
            result[tree[i].arr[j]] = i;
        }
    }
    for (int i = 1; i < n_nodes; ++i) {
        printf("%d %d\n", i, result[i]);
    }

    for (int i = 0; i < n_nodes; ++i) {
        vector_free(nodes[i]);
        vector_free(tree[i]);
    }
    heap_free(heap);
    free(result);
    return 0;
}
// 11 + 25 + 3388 + 1974 + 1738 + 3592 + 11908 = 22636
