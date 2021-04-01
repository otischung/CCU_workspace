// This program is written by Ray Chung.

// 10 2 8 * + 3 -    ->  23.00
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define s_idx idx_s // for TYPO, I don't wanna waste time to fix this
#define idx_s (*get_static_idx())
#define stack _stack()
 
 
typedef union T {
    double f;
    char c;
} T;
 
T* _stack (){
    static T *s;
    if (s == NULL) s = (T*)malloc(sizeof(T) * 819200);
    return s;
}
static inline int *get_static_idx() {
    static int n;
    return &n;
}
 
static inline T pop() {
    assert(idx_s > -1 && "pop");
    return stack[idx_s--];
}
static inline void push(T val) {
    stack[++idx_s] = val;
}
static inline T top() {
    return stack[idx_s];
}
static inline int empty() {
    return s_idx <= -1;
}
int main(void) {
    static char buf[8192];
    static char buf2[8192];
    START:
    s_idx = -1;
    T ans = {.f = 0};
    while (~fscanf(stdin, "%s[^\n]", buf)) {
        if (strlen(buf) == 1 && strstr("+-*/", buf)) {
            T b = pop();
            T a = pop();
            
            const char op = buf[0];
            switch (op) {
                case '+':
                    ans.f = a.f + b.f;
                    break;
                case '-':
                    ans.f = a.f - b.f;
                    break;
                case '*':
                    ans.f = a.f * b.f;
                    break;
                case '/':
                    ans.f = a.f / b.f;
                    break;
            }
            
            push(ans);
            // fprintf(stderr, "#%c %lf\n",op,  ans.f);
        } else {
            T tmp;
            sscanf(buf, "%lf", &tmp.f);
            ans = tmp;
            push(tmp);
        }
        int c = getchar();
        if (c == '\n') {
            printf("%.02lf\n", ans.f);
            goto START;
        } 
    }
}
