// You can check memery leak with `valgrind --leak-check=full --show-leak-kinds=all --verbose <executable file>`
#include "randint_gen.h"
#include "bst.h"
#include "bs.h"
#include "array.h"
#include "linked_list.h"
#include "hash.h"
#include <libgen.h>

/***********************************************************************************
 * -d N (required) 插入的資料筆數，每筆資料是唯一的 (1e+4, 1e+5, 1e+6)
 * -q M (required) 查詢資料筆數 (1e+3, 1e+4, 1e+5)
 * -bst: 測量BST建立和查詢所需時間
 * -bs:  測量 Binary Search建立資料結構(含 sorting) 和查詢所需時間
 * -arr: 測量 array 建立資料結構和查詢(linear search)所需時間
 * -ll: 測量 linked list 建立資料結構和查詢所需時間
 * -hash 測量 hash 建立資料結構和查詢所需時間
 ***********************************************************************************/

void usage(char *);

int main(int argc, char **argv) {
    int insert, query;
    char *processname;

    processname = basename(argv[0]);
    if (argc < 6) {
        usage(processname);
        exit(1);
    }
    if (strcmp("-d", argv[1]) || strcmp("-q", argv[3])) {
        usage(processname);
        exit(1);
    }
    
    insert = (int)atof(argv[2]);
    query = (int)atof(argv[4]);

    //----------------------------------------------------------------------------//

    randint_gen(insert);
    for (int i = 5; i < argc; ++i) {
             if (!strcmp("-bst",  argv[i])) binary_search_tree(insert, query);
        else if (!strcmp("-bs",   argv[i])) binary_search(insert, query);
        else if (!strcmp("-arr",  argv[i])) array_linear_search(insert, query);
        else if (!strcmp("-ll",   argv[i])) linked_list(insert, query);
        else if (!strcmp("-hash", argv[i])) hash(insert, query);
        else {
            usage(processname);
            exit(1);
        }
    }
    return 0;
}

void usage(char *name) {
    fprintf(stderr, "format error\n");
    fprintf(stderr, "usage: ./%s -d <N> -q <M> [-bst] [-bs] [-arr] [-ll] [-hash]\n", name);
    fprintf(stderr, "The process will insert N unique datas and query M datas by using given method.\n");
}

// void *file2array(FILE *fp, int *arr, int start, int end) {
//     int num;
//     fseek(fp, start, SEEK_SET);
//     for (int i = start; i < end; ++i) {
//         fscanf(fp, "%d", &num);
//         arr[i] = num;
//     }
// }
