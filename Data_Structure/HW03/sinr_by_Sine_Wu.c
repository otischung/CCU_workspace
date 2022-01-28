// WA (2021.12.06 12:57)
#pragma GCC optimize("O3")
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NODE {
    int x, y;  // coordinate of the node
    bool used;
} Node;

typedef struct LINK {
    int tran, recv, dist3;  // transmitter, receiver and distance^2
} Link;

double dist2(Node a, Node b) {
    return (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y);  // distance^2
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    const int n_nodes, n_links, power, noise;
    int id, x, y;
    int ac_links;
    int *ac_link_arr;
    Node *n;
    Link *l;
    double sum;
    int max_dist3, M;

    // read data
    scanf("%d %d %d %d", &n_nodes, &n_links, &power, &noise);
    const double n_p = noise / power;  // noise/power
    n = (Node *)malloc(n_nodes * sizeof(Node));
    l = (Link *)malloc(n_links * sizeof(Link));
    ac_link_arr = (int *)calloc(n_links, sizeof(int));
    memset(ac_link_arr, -1, sizeof(ac_link_arr[0]));
    for (int i = 0; i < n_nodes; ++i) {
        scanf("%d %d %d", &id, &x, &y);
        n[id].x = x;
        n[id].y = y;
        n[id].used = false;
    }
    for (int i = 0; i < n_links; ++i) {
        scanf("%d %d %d", &id, &x, &y);
        l[id].tran = x;
        l[id].recv = y;
        l[id].dist3 = pow(dist2(n[x], n[y]), 1.5);
    }

    // process data
    ac_links = 0;
    sum = 0;
    max_dist3 = -1;

    for (int i = 0; i < n_links; ++i) {
        if (n[l[i].tran].used || n[l[i].recv].used)
            continue;
        n[l[i].tran].used = n[l[i].recv].used = true;
        ac_link_arr[ac_links++] = i;
        sum += 1.0 / l[i].dist3;
        M = max(max_dist3, l[i].dist3);
        if (sum + n_p < 2.0 / M)
            max_dist3 = M;
        else {
            n[l[i].tran].used = n[l[i].recv].used = false;
            ac_link_arr[--ac_links] = -1;
            sum -= 1.0 / l[i].dist3;
        }
    }

    // output result
    printf("%d\n", ac_links);
    for (int i = 0; i < ac_links; ++i)
        printf("%d %d %d\n", ac_link_arr[i], ac_link_arr[i][l].tran, ac_link_arr[i][l].recv);

    free(ac_link_arr);
    free(l);
    free(n);
    return 0;
}
