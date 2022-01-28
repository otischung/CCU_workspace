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
    int tran, recv;  // transmitter and recevier
} Link;

double distance(Node a, Node b) {
    return sqrt((double)((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
}

double other_link_noise(Node *n, Link *l, int *ac_link_arr, int ac_links, int power, int choose) {
    double total;
    double dist;

    total = 0;
    dist = 0;
    for (int i = 0; i < ac_links; ++i) {
        if (ac_link_arr[i] == choose) {
            continue;
        }
        dist = distance(n[l[ac_link_arr[i]].tran], n[l[choose].recv]);
        dist = dist * dist * dist;
        total += (double)power / dist;
    }
    return total;
}

double sinr(Node *n, Link *l, int *ac_link_arr, int ac_links, int power, int noise, int choose) {
    double self;
    double dist;

    dist = distance(n[l[choose].tran], n[l[choose].recv]);
    dist = dist * dist * dist;
    self = (double)power / dist;

    return self / (other_link_noise(n, l, ac_link_arr, ac_links, power, choose) + noise);
}

int main() {
    int n_nodes, n_links, power, noise;
    int id, x, y;
    int ac_links;
    int *ac_link_arr;
    Node *n;
    Link *l;

    // read data
    scanf("%d %d %d %d", &n_nodes, &n_links, &power, &noise);
    n = (Node *)malloc(n_nodes * sizeof(Node));
    l = (Link *)malloc(n_links * sizeof(Link));
    ac_link_arr = (int *)calloc(n_links, sizeof(int));
    ac_links = 0;
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
    }

    // process data
    for (int i = 0; i < n_links; ++i) {
        if (n[l[i].tran].used || n[l[i].recv].used) {
            continue;
        }
        n[l[i].tran].used = true;
        n[l[i].recv].used = true;
        ac_link_arr[ac_links++] = i;
        for (int j = 0; j < ac_links; ++j) {
            if (sinr(n, l, ac_link_arr, ac_links, power, noise, ac_link_arr[j]) <= 1.0) {
                n[l[i].tran].used = false;
                n[l[i].recv].used = false;
                ac_link_arr[--ac_links] = -1;
                break;
            }
        }
    }

    // output result
    printf("%d\n", ac_links);
    for (int i = 0; i < ac_links; ++i) {
        printf("%d %d %d\n", ac_link_arr[i], l[ac_link_arr[i]].tran, l[ac_link_arr[i]].recv);
    }

    free(ac_link_arr);
    free(l);
    free(n);
    return 0;
}
