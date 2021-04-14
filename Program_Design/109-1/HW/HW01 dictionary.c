#include <stdio.h>
#include <string.h>

struct node{
    char ch[100];
    char en[100];
};

int main(){
    struct node n[10] = { "電腦", "computer",
                          "鑰匙", "key",
                          "程式碼", "code",
                          "當掉", "flunk",
                          "陣列", "array",
                          "記憶體區段錯誤", "segmentation fault",
                          "匯流排錯誤", "bus error",
                          "字元", "char",
                          "整數", "integer",
                          "浮點數", "floating point"}; 

    char input[100];
    //printf("%d", strcmp(input, n[0].ch));
    while(scanf("%s", input) != EOF){
        for(int i = 0; i < 11; ++i){
            //int same = strcmp(input, n[i].ch);
            //printf("%d", same);
            if (i == 10){
                printf("這啥鬼?\n");
                break;
            }
            if(!strcmp(input, n[i].ch)){
                printf("%s\n", n[i].en);
                break;
            }
        }
    }
    getchar();
    return 0;
}

/* stdin
電腦
鑰匙
程式碼
當掉
陣列
記憶體區段錯誤
匯流排錯誤
字元
整數
浮點數
幹
*/
