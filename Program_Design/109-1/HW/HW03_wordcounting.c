#include <stdio.h>

int main(){
    char input;
    int alpha[26] = { 0 };
    double _alpha[26] = { 0 };
    int number[10] = { 0 };
    double _number[10] = { 0 };
    int size = 0, i, max = 0, min = 2147483647;
    while((input = getchar()) != EOF){
        if((int)input > 47 && (int)input < 58){
            ++number[(int)input - 48];
            ++size;
        }
        else if((int)input > 64 && (int)input < 91){
            ++alpha[(int)input - 65];
            ++size;
        }
        else if((int)input > 96 && (int)input < 123){
            ++alpha[(int)input - 97];
            ++size;
        }
    }
    for(i = 0; i < 26; ++i)
        _alpha[i] = (double)alpha[i] / size;
    for(i = 0; i < 10; ++i){
        _number[i] = (double)number[i] / size;
        if(max < number[i]) max = number[i];
        if(min > number[i]) min = number[i];
    }

    printf("Alphabet statistics:\n");
    for(i = 0; i < 26; ++i)
        printf("%c:\t%d\t%.4lf\n", i + 97, alpha[i], _alpha[i]);
    printf("Number statistics:\n");
    for(i = 0; i < 10; ++i)
        printf("%d:\t%d\t%.4lf\n", i, number[i], _number[i]);
    printf("Most frequently number:\n");
    for(i = 0; i < 10; ++i){
        if(max == number[i])
            printf("%d:\t%d\n", i, number[i]);
    }
    printf("Least frequently number:\n");
    for(i = 0; i < 10; ++i){
        if(min == number[i])
            printf("%d:\t%d\n", i, number[i]);
    }
    return 0;
}
