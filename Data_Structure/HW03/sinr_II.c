#pragma GCC optimize("O3")
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#define forever while (1)

typedef struct NODE {
    int x, y;  // coordinate of the node
    bool used;
} Node;

typedef struct LINK {
    int id;
    int tran, recv;  // transmitter and recevier
    double self_noise;
} Link;

int cmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

double distance(Node a, Node b) {
    return sqrt((double)((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
}

double self_noise(Node *n, Link *l, int power, int choose) {
    double dist;

    dist = distance(n[l[choose].tran], n[l[choose].recv]);
    dist = dist * dist * dist;
    return (double)power / dist;
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
    double self, other;

    self = l[choose].self_noise;
    other = other_link_noise(n, l, ac_link_arr, ac_links, power, choose) + (double)noise;
    return self / other;
}

int main() {
    int n_nodes, n_links, power, noise;
    int id, x, y;
    int ac_links, max_ac_links;
    int *ac_link_arr, *max_ac_link_arr;
    Node *n;
    Link *l;
    struct timeval start, end;

    // read data
    scanf("%d %d %d %d", &n_nodes, &n_links, &power, &noise);
    n = (Node *)malloc(n_nodes * sizeof(Node));
    l = (Link *)malloc(n_links * sizeof(Link));
    ac_link_arr = (int *)calloc(n_links, sizeof(int));
    max_ac_link_arr = (int *)calloc(n_links, sizeof(int));
    ac_links = 0;
    max_ac_links = 0;
    memset(ac_link_arr, -1, ac_links * sizeof(ac_link_arr[0]));
    for (int i = 0; i < n_nodes; ++i) {
        scanf("%d %d %d", &id, &x, &y);
        n[id].x = x;
        n[id].y = y;
        n[id].used = false;
    }
    for (int i = 0; i < n_links; ++i) {
        scanf("%d %d %d", &id, &x, &y);
        l[id].id = i;
        l[id].tran = x;
        l[id].recv = y;
        l[id].self_noise = self_noise(n, l, power, id);
    }

    // process data
    gettimeofday(&start, NULL);
    ac_links = 0;
    memset(ac_link_arr, -1, ac_links * sizeof(ac_link_arr[0]));
    for (id = 0; id < n_links; ++id) {
        // method 1: id, 0, 1, 2, ..., n_links
        n[l[id].tran].used = true;
        n[l[id].recv].used = true;
        ac_link_arr[ac_links++] = id;
        if (sinr(n, l, ac_link_arr, ac_links, power, noise, id) <= 1.0) {
            n[l[id].tran].used = false;
            n[l[id].recv].used = false;
            ac_link_arr[--ac_links] = -1;
            gettimeofday(&end, NULL);
            continue;
        }
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
        if (max_ac_links < ac_links) {
            max_ac_links = ac_links;
            for (int i = 0; i < max_ac_links; ++i) {
                max_ac_link_arr[i] = ac_link_arr[i];
            }
            qsort(max_ac_link_arr, max_ac_links, sizeof(int), cmp);
        }
        gettimeofday(&end, NULL);
        if ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec) >= 8000000) {
            break;
        }

        for (int i = 0; i < ac_links; ++i) {
            n[l[i].tran].used = false;
            n[l[i].recv].used = false;
        }
        ac_links = 0;
        memset(ac_link_arr, -1, ac_links * sizeof(ac_link_arr[0]));

        // method 2: id, id + 1, id + 2, ..., n_links, 0, 1, ..., id - 1

        for (int i = id; i < n_links; ++i) {
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
        for (int i = 0; i < id; ++i) {
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
        if (max_ac_links < ac_links) {
            max_ac_links = ac_links;
            for (int i = 0; i < max_ac_links; ++i) {
                max_ac_link_arr[i] = ac_link_arr[i];
            }
            qsort(max_ac_link_arr, max_ac_links, sizeof(int), cmp);
        }
        gettimeofday(&end, NULL);
        if ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec) >= 8000000) {
            break;
        }

        for (int i = 0; i < ac_links; ++i) {
            n[l[i].tran].used = false;
            n[l[i].recv].used = false;
        }
        ac_links = 0;
        memset(ac_link_arr, -1, ac_links * sizeof(ac_link_arr[0]));
    }

    // output result
    printf("%d\n", max_ac_links);
    for (int i = 0; i < max_ac_links; ++i) {
        printf("%d %d %d\n", max_ac_link_arr[i], l[max_ac_link_arr[i]].tran, l[max_ac_link_arr[i]].recv);
    }

    free(max_ac_link_arr);
    free(ac_link_arr);
    free(l);
    free(n);
    return 0;
}
// AC_links: 656
