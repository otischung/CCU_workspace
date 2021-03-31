#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MaxNameLen 1024
#define MaxStudentCnt 1024

typedef struct TRANSCRIPT {
    char name[MaxNameLen];
    int HW[5];
    int sum;
} Transcript;

int cmp(const void *, const void *);


////////////////////////////////////////////////////////////
int main() {
    Transcript student[1024];
    int stuCnt = 0;

    while (~scanf("%s %d %d %d %d %d",\
     student[stuCnt].name,  &student[stuCnt].HW[0],\
    &student[stuCnt].HW[1], &student[stuCnt].HW[2],\
    &student[stuCnt].HW[3], &student[stuCnt].HW[4])) {
        student[stuCnt].sum = student[stuCnt].HW[0] +\
                              student[stuCnt].HW[1] +\
                              student[stuCnt].HW[2] +\
                              student[stuCnt].HW[3] +\
                              student[stuCnt].HW[4];
        ++stuCnt;
    }

    qsort(student, stuCnt, sizeof(Transcript), cmp);

    for (int i = 0; i < stuCnt; ++i) {
        printf("%s\t%d\t%d\t%d\t%d\t%d\n",\
        student[i].name,  student[i].HW[0],\
        student[i].HW[1], student[i].HW[2],\
        student[i].HW[3], student[i].HW[4]);
    }

    return 0;
}
////////////////////////////////////////////////////////////


int cmp(const void *_a, const void *_b) {
    Transcript *a = (Transcript *)_a;
    Transcript *b = (Transcript *)_b;

    return b->sum - a->sum;
}