#include <stdio.h>
#include <string.h>

void table(int b, int e, int s){
    int k = b;
    double t = (double)k * 1.66;
    while (k < e){
        printf("%d\t%.2lf\n", k, t);
        k += s;
        t = (double)k * 1.66;
    }
}

int main(){
    int begin, end, step;
    scanf("%d %d %d", &begin, &end, &step);
    printf("公斤\t台斤\n");
    table(begin, end, step);

    int kilo;
    double tai;
    while(scanf("%d", &kilo) != EOF){
        if (kilo < 0) break;
        tai = (double)kilo * 1.66;
        printf("%.2lf\n", tai);
    }

    return 0;
}

/*
0 5 1
20 
5
-1
*/